/*
 * main.c
 *
 *  Created on: 2023.4.20
 *      Author: Shine_hale
 *  实时获取16位开关的状态，并将16位开关分为高13位（SW15~3）、低3位（SW2~0）两部分，
 *  要求将SW15~3 13位无符号二进制数（D12~0）表示的十进制数显示在8位七段数码管上，
 *  且最高位从SW2~0（1≤SW2~0≤5）所指示位置开始显示，无数据数码管灭。
 *  即若SW15~0=0xfff9，结果如图所示
 *
 */


#include "xgpio_l.h"
#include "xparameters.h"
#include "xil_io.h"
#include "xil_exception.h"
#include "xintc_l.h"
#include "xtmrctr_l.h"

const int reset_value = 100000 - 2;
unsigned char segs[16] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
					0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};

void setup_interrupt(void);
void setup_timer_system(void);
void event_handler(void) __attribute__((fast_interrupt));
void timer_handler(void) __attribute__((fast_interrupt));

unsigned short data_out[4] = {0, 0, 0, 0};
unsigned short seg_pos = 0xbf, data_pos = 0, std_pos = 0;

int main(){

	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI_OFFSET, 0x0000ffff);
	Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI2_OFFSET, 0x00);

	setup_interrupt();
	return 0;
}

void setup_interrupt(void) {

	/*GPIO settings*/
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_IER_OFFSET, XGPIO_IR_CH1_MASK);		//enable the channel 1 interrupt
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_ISR_OFFSET, XGPIO_IR_CH1_MASK);		//clear the channel 1 interrupt status
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_GIE_OFFSET, XGPIO_GIE_GINTR_ENABLE_MASK);  	//enable GPIO interrupt and output


	/*timer initialization*/
	Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TLR_OFFSET, reset_value);
	Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET, Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET) | XTC_CSR_LOAD_MASK);
	Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET, Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET) & ~XTC_CSR_LOAD_MASK);
	Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET, (Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET) & ~XTC_CSR_LOAD_MASK)
				| XTC_CSR_ENABLE_TMR_MASK | XTC_CSR_AUTO_RELOAD_MASK | XTC_CSR_ENABLE_INT_MASK | XTC_CSR_DOWN_COUNT_MASK);
	Xil_Out32(XPAR_TMRCTR_0_BASEADDR+XTC_TCSR_OFFSET,
				Xil_In32(XPAR_TMRCTR_0_BASEADDR+XTC_TCSR_OFFSET )|
						XTC_CSR_INT_OCCURED_MASK| XTC_CSR_ENABLE_INT_MASK);


	/* set up the INTC */
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IMR_OFFSET, XPAR_AXI_GPIO_0_IP2INTC_IRPT_MASK | XPAR_AXI_TIMER_0_INTERRUPT_MASK);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IAR_OFFSET, XPAR_AXI_GPIO_0_IP2INTC_IRPT_MASK | XPAR_AXI_TIMER_0_INTERRUPT_MASK);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IER_OFFSET, XPAR_AXI_GPIO_0_IP2INTC_IRPT_MASK | XPAR_AXI_TIMER_0_INTERRUPT_MASK);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_MER_OFFSET, XIN_INT_MASTER_ENABLE_MASK | XIN_INT_HARDWARE_ENABLE_MASK);

	/* sign up the interrupt handler functions in the IVAR*/
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IVAR_OFFSET +
				4 * XPAR_AXI_INTC_0_AXI_TIMER_0_INTERRUPT_INTR, (unsigned int)timer_handler);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IVAR_OFFSET +
				4 * XPAR_AXI_INTC_0_AXI_GPIO_0_IP2INTC_IRPT_INTR, (unsigned int)event_handler);
	microblaze_enable_interrupts();
}
void timer_handler(void) {
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA2_OFFSET, ((seg_pos & 0xff) << 8) + data_out[data_pos]);
	data_pos += 1;
	if (data_pos == 4) data_pos = 0;
	seg_pos = (seg_pos << 1) + 1;
	if ((seg_pos & 0xff) == (((std_pos << 4) + 0xf) & 0xff)) seg_pos = std_pos;

	unsigned int status = Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET);
	if ((status & XTC_CSR_INT_OCCURED_MASK) == XTC_CSR_INT_OCCURED_MASK)
			Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET, Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET));
}

void event_handler(void) {


	unsigned short SW_status = Xil_In16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA_OFFSET);		// read the data from the switches.
	unsigned short switch_data = (SW_status >> 3) & 0x1fff;
	unsigned short pos_in = SW_status & 0x7;
	int i = 0;
	unsigned data = 0;
	while (switch_data) {
		data = (data << 4) + switch_data % 10;
		switch_data = switch_data / 10;
	}
	for (i = 3; i >= 0; i--) {
		data_out[i] = segs[data & 0xf];
		data = data >> 4;
	}
	switch (pos_in) {
		case 5:
			std_pos = 0xfe;
			break;
		case 4:
			std_pos = 0xfd;
			break;
		case 3:
			std_pos = 0xfb;
			break;
		case 2:
			std_pos = 0xf7;
			break;
		case 1:
			std_pos = 0xef;
			break;
		default:
			std_pos = 0xff;
			break;
	}
	seg_pos = std_pos;
	data_pos = 0;
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_ISR_OFFSET, Xil_In32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_ISR_OFFSET));
}
