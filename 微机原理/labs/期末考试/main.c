/*
 * main.c
 *
 *  Created on: 2023ƒÍ5‘¬17»’
 *      Author: —ÓÛﬁÀ…
 */


#include "xintc_l.h"
#include "xtmrctr_l.h"
#include "xgpio_l.h"
#include "xparameters.h"
#include "xio.h"
#include "xil_exception.h"

unsigned char segs[16] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
					0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};


unsigned short status = 0, lst_status = 0;
unsigned short data = 0, pos = 1, flag = 0, begin = 0;
const unsigned int reset_value = 100000000-2;


void buttun_handler() __attribute__ ((fast_interrupt)); // intr(0)
void timer_handler() __attribute__ ((fast_interrupt));// intr(2)
void setup_interrupt(void);

int main(){
	Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI_OFFSET, 0xffff); 		// set SW as input
	Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI2_OFFSET, 0x0);			// set LED as output
	Xil_Out16(XPAR_AXI_GPIO_2_BASEADDR + XGPIO_TRI_OFFSET, 0xffff);			// set BTND, U, L, R, C as input
	Xil_Out32(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_TRI_OFFSET, 0x0);			// set the display of the case.
	Xil_Out32(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_TRI2_OFFSET, 0x0);

	setup_interrupt();

	return 0;
}

void setup_interrupt(void){


	Xil_Out32(XPAR_AXI_GPIO_2_BASEADDR + XGPIO_IER_OFFSET, XGPIO_IR_CH1_MASK);		//enable the channel 1 interrupt
	Xil_Out32(XPAR_AXI_GPIO_2_BASEADDR + XGPIO_ISR_OFFSET, XGPIO_IR_CH1_MASK);		//clear the channel 1 interrupt status
	Xil_Out32(XPAR_AXI_GPIO_2_BASEADDR + XGPIO_GIE_OFFSET, XGPIO_GIE_GINTR_ENABLE_MASK);	//enable GPIO interrupt and output


	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IMR_OFFSET, XPAR_AXI_GPIO_2_IP2INTC_IRPT_MASK | XPAR_AXI_TIMER_0_INTERRUPT_MASK);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IAR_OFFSET, XPAR_AXI_GPIO_2_IP2INTC_IRPT_MASK | XPAR_AXI_TIMER_0_INTERRUPT_MASK);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IER_OFFSET, XPAR_AXI_GPIO_2_IP2INTC_IRPT_MASK | XPAR_AXI_TIMER_0_INTERRUPT_MASK);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_MER_OFFSET, XIN_INT_MASTER_ENABLE_MASK | XIN_INT_HARDWARE_ENABLE_MASK);

	/*timer initialization*/
	Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TLR_OFFSET, reset_value);
	Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET, Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET) | XTC_CSR_LOAD_MASK);
	Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET, Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET) & ~XTC_CSR_LOAD_MASK);
	Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET, (Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET) & ~XTC_CSR_LOAD_MASK)
				| XTC_CSR_ENABLE_TMR_MASK | XTC_CSR_AUTO_RELOAD_MASK | XTC_CSR_ENABLE_INT_MASK | XTC_CSR_DOWN_COUNT_MASK);
	Xil_Out32(XPAR_TMRCTR_0_BASEADDR+XTC_TCSR_OFFSET,
				Xil_In32(XPAR_TMRCTR_0_BASEADDR+XTC_TCSR_OFFSET )|
						XTC_CSR_INT_OCCURED_MASK| XTC_CSR_ENABLE_INT_MASK);

	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IVAR_OFFSET +
					4 * XPAR_AXI_INTC_0_AXI_TIMER_0_INTERRUPT_INTR, (unsigned int)timer_handler);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IVAR_OFFSET +
					4 * XPAR_INTC_0_GPIO_2_VEC_ID, (unsigned int)buttun_handler);			// make the address into the IVAR
	microblaze_enable_interrupts();
}
void timer_handler()
{
	unsigned short target_data = segs[data];
	unsigned short datapos = (1<<pos); datapos = (~datapos) & 0xff;
	if (flag == 1) {

		Xil_Out8(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_DATA_OFFSET, datapos);
		Xil_Out8(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_DATA2_OFFSET, target_data);
		pos = pos + 1;
		if (pos == 8) {
			pos = 0;
		}
	} else if (begin == 1) {
		Xil_Out8(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_DATA_OFFSET, datapos);
		Xil_Out8(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_DATA2_OFFSET, target_data);
	}
	else {
		Xil_Out8(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_DATA_OFFSET, 0xff);
		Xil_Out8(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_DATA2_OFFSET, 0xff);
	}

	unsigned int status = Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET);
		if ((status & XTC_CSR_INT_OCCURED_MASK) == XTC_CSR_INT_OCCURED_MASK)
				Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET, Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET));

}

void buttun_handler(void) {
	status = Xil_In16(XPAR_AXI_GPIO_2_BASEADDR + XGPIO_DATA_OFFSET) & 0x1f;
	if (lst_status != status) {
		lst_status = status;
		if (status & 0x1) {
			data =  Xil_In16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA_OFFSET) & 0xf;
			xil_printf("%x\n", data);
			pos = 0;
			begin = 1;
			flag = 0;
			unsigned short target_data = segs[data] & 0xff;
			unsigned short datapos = (1<<pos); datapos = (~datapos) & 0xff;
			Xil_Out8(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_DATA_OFFSET, datapos);
			Xil_Out8(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_DATA2_OFFSET, target_data);
		} else if (status &0x4) {
			flag = 1;
		}
	}
	Xil_Out32(XPAR_GPIO_2_BASEADDR + XGPIO_ISR_OFFSET, XGPIO_IR_CH1_MASK);
}
