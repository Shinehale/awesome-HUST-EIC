/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/


#include "stdio.h"
#include "xparameters.h"
#include "xil_exception.h"
#include "xil_io.h"
#include "xio.h"
#include "xgpio_l.h"
#include "xtmrctr_l.h"
#include "xintc_l.h"
#include "xspi_l.h"
#define T0_RESET_VALUE_MIN 1000-2 // 60ms
#define T0_RESET_VALUE_MAX 20000-2 // 1.2S
void switch_handler() __attribute__ ((fast_interrupt)); // intr(0)
void timer_handler() __attribute__ ((fast_interrupt));// intr(2)
//void DA_handler() __attribute__ ((fast_interrupt));//intr(3)
u16 volt, lastvolt;
int main()
{

	//GPIO0 switch and led
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI_OFFSET, 0x0000ffff);// set switches input and led output
	Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI2_OFFSET, 0x0);// set segment display

	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_ISR_OFFSET, XGPIO_IR_CH1_MASK|XGPIO_IR_CH2_MASK);// CLEAR INTERRUPT
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_IER_OFFSET, XGPIO_IR_CH1_MASK);// ENABLE INTERRUPT OF CH1
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_GIE_OFFSET, XGPIO_GIE_GINTR_ENABLE_MASK);//ENABLE GLOBAL INTERRUPT

	//SPI
		//RESET
	Xil_Out32(XPAR_AXI_QUAD_SPI_0_BASEADDR + XSP_SRR_OFFSET,XSP_SRR_RESET_MASK );
	   //SPI MASTER MODE   CPOL = 1 CPHA = 0
	Xil_Out32(XPAR_AXI_QUAD_SPI_0_BASEADDR + XSP_CR_OFFSET, XSP_CR_ENABLE_MASK|\
			XSP_CR_MASTER_MODE_MASK|XSP_CR_CLK_POLARITY_MASK);
	   //SET SSR to select slave0
	Xil_Out32(XPAR_AXI_QUAD_SPI_0_BASEADDR + XSP_SSR_OFFSET, 0xfffffffe);
	   //ENABLE SPI INTERRUPT
	Xil_Out32(XPAR_AXI_QUAD_SPI_0_BASEADDR + XSP_IIER_OFFSET, XSP_INTR_TX_EMPTY_MASK);
	Xil_Out32(XPAR_AXI_QUAD_SPI_0_BASEADDR + XSP_DGIER_OFFSET, XSP_GINTR_ENABLE_MASK);

	//TIMER
	int tcsr0;
	tcsr0 = Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET);// TO GET THE VALUE 0F TCSR
		Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET,tcsr0&~XTC_CSR_ENABLE_TMR_MASK);// STOP THE COUNTER
		Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TLR_OFFSET,T0_RESET_VALUE_MIN);//preset value
		Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET,tcsr0|XTC_CSR_LOAD_MASK);// LOAD THE PRESET VALUE
		Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET,(tcsr0&~XTC_CSR_LOAD_MASK)|XTC_CSR_ENABLE_TMR_MASK|XTC_CSR_AUTO_RELOAD_MASK|\
		XTC_CSR_ENABLE_INT_MASK|XTC_CSR_DOWN_COUNT_MASK|XTC_CSR_INT_OCCURED_MASK);// NO LOAD;ENABLE COUNT;AUTO RELOAD;ENABLE INT; CLEAR INT

	//INTC
		Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IAR_OFFSET, \
				XPAR_AXI_QUAD_SPI_0_IP2INTC_IRPT_MASK|XPAR_AXI_GPIO_0_IP2INTC_IRPT_MASK|XPAR_AXI_TIMER_0_INTERRUPT_MASK );//clear interrupt
	    Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IMR_OFFSET, \
	    		XPAR_AXI_QUAD_SPI_0_IP2INTC_IRPT_MASK|XPAR_AXI_GPIO_0_IP2INTC_IRPT_MASK|XPAR_AXI_TIMER_0_INTERRUPT_MASK);//fast interrupt
		Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IER_OFFSET, \
				XPAR_AXI_QUAD_SPI_0_IP2INTC_IRPT_MASK|XPAR_AXI_GPIO_0_IP2INTC_IRPT_MASK|XPAR_AXI_TIMER_0_INTERRUPT_MASK);// interrupt enable
		Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_MER_OFFSET,XIN_INT_MASTER_ENABLE_MASK|XIN_INT_HARDWARE_ENABLE_MASK);// master enable

		Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IVAR_OFFSET, (int)XPAR_INTC_0_SPI_0_VEC_ID);
		Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IVAR_OFFSET + 4*XPAR_INTC_0_GPIO_0_VEC_ID,(int)switch_handler);//
		Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IVAR_OFFSET + 4*XPAR_INTC_0_TMRCTR_0_VEC_ID,(int)timer_handler);//
		microblaze_enable_interrupts();


		Xil_Out16(XPAR_AXI_QUAD_SPI_0_BASEADDR + XSP_DTR_OFFSET, 0);
		return 0;
}
//void DA_handler()
//{
//	// Clear SPI interrupt
//	Xil_Out32(XPAR_AXI_QUAD_SPI_0_BASEADDR + XSP_IISR_OFFSET, Xil_In32(XPAR_AXI_QUAD_SPI_0_BASEADDR + XSP_IISR_OFFSET));
//	volt++;
//	Xil_Out32(XPAR_AXI_QUAD_SPI_0_BASEADDR + XSP_DTR_OFFSET, volt&0xfff);
//}
void timer_handler()
{
	int status;
	status =Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET);
	if ((status&XTC_CSR_INT_OCCURED_MASK )== XTC_CSR_INT_OCCURED_MASK)
	{
		volt++;
		Xil_Out32(XPAR_AXI_QUAD_SPI_0_BASEADDR + XSP_DTR_OFFSET, volt&0xfff);
		Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET,status);
	}

}
void switch_handler()
{
	 unsigned short hex = Xil_In16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA_OFFSET);
	int reset_value =(int)((T0_RESET_VALUE_MAX - T0_RESET_VALUE_MIN)/65000.0 * hex)+ T0_RESET_VALUE_MIN;
	int tcsr0 = Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET);// TO GET THE VALUE 0F TCSR
	Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET,tcsr0&~XTC_CSR_ENABLE_TMR_MASK);// STOP THE COUNTER
	Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TLR_OFFSET,reset_value);//preset value
	Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET,tcsr0|XTC_CSR_LOAD_MASK);// LOAD THE PRESET VALUE
	Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + XTC_TCSR_OFFSET,(tcsr0&~XTC_CSR_LOAD_MASK)|XTC_CSR_ENABLE_TMR_MASK|XTC_CSR_AUTO_RELOAD_MASK|\
			XTC_CSR_ENABLE_INT_MASK|XTC_CSR_DOWN_COUNT_MASK|XTC_CSR_INT_OCCURED_MASK);// NO LOAD;ENABLE COUNT;AUTO RELOAD;ENABLE INT; CLEAR INT

	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_ISR_OFFSET,XGPIO_IR_CH1_MASK);
}

