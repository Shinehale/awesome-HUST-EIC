

/*
 * main.c
 *
 *  Created on: 2023.4.19
 *      Author: Shine_hale
 * 	实时获取16位开关的状态，并及时反映在16位LED对应位上，同时将16位开关对应的4位十六进制数字从高到低依次显示在8位七段数码管的位5~位8上，其余数码管灭。
 */


#include "xgpio_l.h"
#include "xparameters.h"
#include "xil_io.h"
#include "xil_exception.h"
#include "xintc_l.h"
#include "xtmrctr_l.h"

unsigned char segs[16] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
					0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};

void setup_GPIO_interrupt(void);
void General_handler(void) __attribute__((interrupt_handler));
void display_segs(unsigned short);
unsigned short SW_status = 0;

int main(){

	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI_OFFSET, 0x0000ffff);
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI2_OFFSET, 0x00);
	setup_GPIO_interrupt();
	while (1){
		display_segs(SW_status & 0xffff);
	}
	return 0;
}
void setup_GPIO_interrupt(void) {

	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IAR_OFFSET, XPAR_AXI_GPIO_0_IP2INTC_IRPT_MASK);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IER_OFFSET, XPAR_AXI_GPIO_0_IP2INTC_IRPT_MASK);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_MER_OFFSET, XIN_INT_MASTER_ENABLE_MASK | XIN_INT_HARDWARE_ENABLE_MASK);

	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_IER_OFFSET, XGPIO_IR_CH1_MASK);		//enable the channel 1 interrupt
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_ISR_OFFSET, XGPIO_IR_CH1_MASK);		//clear the channel 1 interrupt status
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_GIE_OFFSET, XGPIO_GIE_GINTR_ENABLE_MASK);	//enable GPIO interrupt and output

	microblaze_enable_interrupts();
}
void display_segs(unsigned short data) {
	unsigned short pos = 0xff7f, i = 0, tmp = data;
	for (i = 0; i < 4; i++){
		Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA2_OFFSET,
					((pos & 0xff) << 8) + (segs[tmp & 0xf] & 0xff));
		tmp >>= 4;
		pos >>= 1;
		unsigned int times = 0;
		for (times = 0; times <= 1000; times++);
	}
}
void General_handler(void){

	SW_status = Xil_In16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA_OFFSET) & 0xffff;
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA_OFFSET, SW_status << 16);
	Xil_Out32(XPAR_GPIO_0_BASEADDR + XGPIO_ISR_OFFSET, XGPIO_IR_CH1_MASK);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IAR_OFFSET, XGPIO_IR_CH1_MASK);

}

