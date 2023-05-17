/*
 * main.c
 *
 *  Created on: 2023ƒÍ4‘¬12»’
 *      Author: —ÓÛﬁÀ…
 */


#include "xintc_l.h"
#include "xtmrctr_l.h"
#include "xgpio_l.h"
#include "xparameters.h"
#include "xio.h"
#include "xil_exception.h"

int main(){

	Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI_OFFSET, 0xffff); 		// set SW as input
	Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI2_OFFSET, 0x0);			// set LED as output
	Xil_Out16(XPAR_AXI_GPIO_2_BASEADDR + XGPIO_TRI_OFFSET, 0xffff);			// set BTND, U, L, R, C as input

	unsigned short data1 = 0, data2 = 0, data3 = 0, data4 = 0;
	while (1) {
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
			Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA2_OFFSET, data3);
		}
		if (status & 0x2) {
			data4 = data1 + data2;
			Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA2_OFFSET, data4);
		}
	}

}
