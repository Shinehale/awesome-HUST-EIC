/*
 * main.c
 *
 *  Created on: 2023年4月12日
 *      Author: 杨筠松
 */


/*
 * main.c
 *
 *  Created on: 2023年4月12日
 *      Author: 杨筠松
 */


#include "xintc_l.h"
#include "xtmrctr_l.h"
#include "xgpio_l.h"
#include "xparameters.h"
#include "xio.h"
#include "xil_exception.h"

int interrupt = 0;
void interrupt_hub(void) __attribute__((fast_interrupt));
void setup_GPIO_interrupt(void);


int main(){

	Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI_OFFSET, 0xffff); 		// set SW as input
	Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI2_OFFSET, 0x0);			// set LED as output
	Xil_Out16(XPAR_AXI_GPIO_2_BASEADDR + XGPIO_TRI_OFFSET, 0xffff);			// set BTND, U, L, R, C as input
	setup_GPIO_interrupt();
	return 0;
}

unsigned short data1 = 0, data2 = 0, data3 = 0, data4 = 0;
void interrupt_hub(void) {
	xil_printf("this is in the interrupt\n");
	unsigned short status = 0;
	status = Xil_In16(XPAR_AXI_GPIO_2_BASEADDR + XGPIO_DATA_OFFSET) & 0x1f;
	if (status & 0x1) {
		data1 = Xil_In16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA_OFFSET);
		Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA2_OFFSET, data1);
	}
	if (status & 0x8) {
		data2 = Xil_In16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA_OFFSET);
		Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA2_OFFSET, data2);
	}
	if (status & 0x10) {
		data3 = data1 * data2;
		xil_printf("this is times case %x\n", data3);
		Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA2_OFFSET, data3);
	}
	if (status & 0x2) {
		data4 = data1 + data2;
		Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA2_OFFSET, data4);
	}
	Xil_Out32(XPAR_GPIO_2_BASEADDR + XGPIO_ISR_OFFSET, XGPIO_IR_CH1_MASK);
}

void setup_GPIO_interrupt(void) {

	Xil_Out32(XPAR_AXI_GPIO_2_BASEADDR + XGPIO_IER_OFFSET, XGPIO_IR_CH1_MASK);		//enable the channel 1 interrupt
	Xil_Out32(XPAR_AXI_GPIO_2_BASEADDR + XGPIO_ISR_OFFSET, XGPIO_IR_CH1_MASK);		//clear the channel 1 interrupt status
	Xil_Out32(XPAR_AXI_GPIO_2_BASEADDR + XGPIO_GIE_OFFSET, XGPIO_GIE_GINTR_ENABLE_MASK);	//enable GPIO interrupt and output

	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IAR_OFFSET, XPAR_AXI_GPIO_2_IP2INTC_IRPT_MASK);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IER_OFFSET, XPAR_AXI_GPIO_2_IP2INTC_IRPT_MASK);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_MER_OFFSET, XIN_INT_MASTER_ENABLE_MASK | XIN_INT_HARDWARE_ENABLE_MASK);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IMR_OFFSET, XPAR_AXI_GPIO_2_IP2INTC_IRPT_MASK);		// set the IMR as the fast interrupt
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IVAR_OFFSET +
				4 * XPAR_INTC_0_GPIO_2_VEC_ID, (unsigned int)interrupt_hub);			// make the address into the IVAR
	microblaze_enable_interrupts();
}
