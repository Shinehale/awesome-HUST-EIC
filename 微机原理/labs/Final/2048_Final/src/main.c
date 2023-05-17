/*
 * main.c
 *
 *  Created on: 23.5.6
 */

#include "xintc_l.h"
#include "xgpio_l.h"
#include "xparameters.h"
#include "xio.h"
#include "xil_exception.h"

#include "display.h"
#include "logic.h"
#define TFT_BASEADDR 0x44a00000
#define TFT_FRAME_BASEADDR 0x80000000


unsigned int maps[4][4] = {0};
int total_scores = 0;


int main(){


	init_display();
	init_game();
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI_OFFSET, 0x1f);
	unsigned short last_status = 0;
	while (1) {
		// loop for reading the statues from the buttons.
		for(int i = 0; i < 100000; i++);

		unsigned short status = 0;
		status = Xil_In16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA_OFFSET) & 0x1f;
		if (status != last_status) {
			last_status = status;
		} else continue;
		int direction = 0;
		switch (status) {
			case 0x2:
				direction = 1;
				break;
			case 0x10:
				direction = 2;
				break;
			case 0x4:
				direction = 3;
				break;
			case 0x8:
				direction = 4;
				break;
			case 0x1:
				init_display();
				init_game();
				break;
			default:
				continue;
		}
		move_forward(direction);
	}
	return 0;
}
