/*
 * main.c
 *
 *  Created on: 2023年4月28日
 *      Author: Shine_hale
 */

#include "xtmrctr_l.h"
#include "xspi_l.h"
#include "xintc_l.h"
#include "xil_io.h"
#include "xil_exception.h"
#include "xgpio_l.h"
#define INTC_IAR  	(XPAR_INTC_0_BASEADDR + XIN_IAR_OFFSET)
#define INTC_ISR  	(XPAR_INTC_0_BASEADDR + XIN_ISR_OFFSET)
#define INTC_IER  	(XPAR_INTC_0_BASEADDR + XIN_IER_OFFSET)
#define INTC_MER  	(XPAR_INTC_0_BASEADDR + XIN_MER_OFFSET)
#define GPIO_TRI  	(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_TRI_OFFSET)
#define GPIO_DATA 	(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_DATA_OFFSET)
#define GPIO_TRI2 	(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_TRI2_OFFSET)
#define GPIO_DATA2 	(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_DATA2_OFFSET)
#define TMRCTR_TLR 	(XPAR_TMRCTR_0_BASEADDR + XTC_TLR_OFFSET)
#define TMRCTR_TCSR (XPAR_TMRCTR_0_BASEADDR + XTC_TCSR_OFFSET)
#define SPI_SRR 	(XPAR_SPI_1_BASEADDR + XSP_SRR_OFFSET)
#define SPI_CR		(XPAR_SPI_1_BASEADDR + XSP_CR_OFFSET)
#define SPI_IIER	(XPAR_AXI_QUAD_SPI_1_BASEADDR + XSP_IIER_OFFSET)
#define SPI_IISR	(XPAR_AXI_QUAD_SPI_1_BASEADDR + XSP_IISR_OFFSET)
#define SPI_DGIER	(XPAR_AXI_QUAD_SPI_1_BASEADDR + XSP_DGIER_OFFSET)
#define SPI_DRR		(XPAR_AXI_QUAD_SPI_1_BASEADDR + XSP_DRR_OFFSET)
#define SPI_DTR		(XPAR_AXI_QUAD_SPI_1_BASEADDR + XSP_DTR_OFFSET)
#define TMRCTR_INIT (XTC_CSR_INT_OCCURED_MASK | XTC_CSR_AUTO_RELOAD_MASK | XTC_CSR_DOWN_COUNT_MASK | XTC_CSR_LOAD_MASK| XTC_CSR_ENABLE_INT_MASK)
#define SPI_INIT 	(XSP_CR_ENABLE_MASK | XSP_CR_MASTER_MODE_MASK | XSP_CR_CLK_POLARITY_MASK | XSP_CR_TXFIFO_RESET_MASK | XSP_CR_RXFIFO_RESET_MASK)
#define RESET_VALUE (20000 - 2)
void TOHandler(void);
void SPIHandler(void);
void My_ISR(void) __attribute__ ((interrupt_handler));
char segtable[10] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x98 };
char segcode[4] = { 0xc0, 0xc0, 0xc0, 0xc0 };
char poscode[4] = { 0x7, 0xb, 0xd, 0xe };
int pos = 0, adc_done = 0;
u16 volt, lastvolt;
int main() {

	 /*
	  * XPAR_AXI_TIMER_0_INTERRUPT_MASK|XPAR_AXI_QUAD_SPI_1_IP2INTC_IRPT_MASK = 0x210
	  * XSP_CR_ENABLE_MASK|XSP_CR_MASTER_MODE_MASK|XSP_CR_CLK_POLARITY_MASK|XSP_CR_TXFIFO_RESET_MASK|XSP_CR_RXFIFO_RESET_MASK = 0x6e
	  */

	int status;
	Xil_Out32(INTC_IAR, Xil_In32(INTC_ISR));
	Xil_Out32(INTC_IER, XGPIO_IR_CH1_MASK);
	Xil_Out32(INTC_MER, XIN_INT_MASTER_ENABLE_MASK | XIN_INT_HARDWARE_ENABLE_MASK);
	microblaze_enable_interrupts();

	Xil_Out32(GPIO_TRI, 0x0);
	Xil_Out32(GPIO_TRI2, 0x0);
	Xil_Out32(TMRCTR_TLR, RESET_VALUE);
	Xil_Out32(TMRCTR_TCSR, TMRCTR_INIT);

	status = Xil_In32(TMRCTR_TCSR);
	status = (status & (~XTC_CSR_LOAD_MASK)) | XTC_CSR_ENABLE_TMR_MASK;
	Xil_Out32(TMRCTR_TCSR, status);
	Xil_Out32(SPI_SRR, XSP_SRR_RESET_MASK);
	Xil_Out32(SPI_CR, SPI_INIT);
	Xil_Out32(SPI_IIER, XSP_INTR_RX_FULL_MASK);
	Xil_Out32(SPI_DGIER, /*XSP_GINTR_ENABLE_MASK*/0x80000000);
	Xil_Out32(SPI_SRR, 0xffffff7f);
	Xil_Out32(SPI_DTR, 0x0);
	while(1) {
		while (!adc_done);
		adc_done = 0; 					//此空填入某个已定义的变量名
		if (volt != lastvolt) { 	//当输入电压变化时更新显示缓冲区
			lastvolt = volt; 		//此空填入某个已定义的变量名
			volt = volt * 3300 / 4095;
			for(int i = 4; i > 0; i--) {//转换为对应的段码
				segcode[i - 1] = segtable[volt % 10];//填入十进制数
				volt = volt / 10 ; //填入十进制数
			}
		}
		Xil_Out32(SPI_DTR, 0x0);//此空填入程序中已经使用过的某个宏
	}
	return 0;
}

void My_ISR(void) {
	int status;
	status = Xil_In32(INTC_ISR);
	if(status & 0x200 )
		SPIHandler();
	if (status & 0x10)
		TOHandler();
	Xil_Out32(INTC_IAR, status);
}
void TOHandler(void) {
	Xil_Out8(GPIO_DATA2, segcode[pos]);
	Xil_Out8(GPIO_DATA, poscode[pos]);
	pos++;
	if(pos == 4) //填入十进制数
		pos = 0;
	Xil_Out32(TMRCTR_TCSR, Xil_In32(TMRCTR_TCSR)); //此空要求填入程序中已经使用过的某个宏
}
void SPIHandler(void) {
	Xil_Out32(SPI_IISR, Xil_In32(SPI_IISR));
	volt = Xil_In16(SPI_DRR) & 0xfff;
	adc_done = 1;
}
