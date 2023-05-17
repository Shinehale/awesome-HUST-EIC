/*
 * display.c
 *
 *  Created on: 23.5.6
 *  Author: Shine_hale
 */

#include "display.h"
#include "image.h"
#include "xil_io.h"

extern unsigned int maps[4][4];


int check_pos(int val){
	int s = 2;
	for (int i = 1; i < 12; i++){
		if (s == val) return i;
		else s = s << 1;
	}
	return 0;
}

void init_display(void) {

	Xil_Out32(TFT_0_BASEADDR + TFT_AR_OFFSET, TFT_FRAME_ADDR0);

	int i, j;
	for (i = 0; i < 480; i++)
		for (j = 0; j < 640; j++)
			Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + j)), 0xffffff);			// clear the screen.

	for (i = 0; i < 16; i++) display_bulk(i, 0);			// plot each grids for image

	for (i = 80; i < 120; i++)
		for (j = 500; j < 618; j++){
			u32 color = Xil_In32((unsigned int)gImage_score + ((i - 80) * 118 + (j - 500)) * 4);
			Xil_Out32(TFT_FRAME_ADDR0 + 4 * (1024 * i + j - 10), color);
		}
	display_score(0);
}
void display_bulk(int pos, int val) {
	int pos_row_start = 30 + (int)(pos / 4) * 110, pos_col_start = 30 + (pos % 4) * 110;
	int i, j;
	for (i = 0; i < 90; i++)
		for (j = 0; j < 90; j++){
			int pos_row = pos_row_start + i, pos_col = pos_col_start + j;
			int addr = (pos_row * 1024 + pos_col) * 4;
			int color = 0x808080;
			if (val != 0) {
				int color_addr = (unsigned int)gImage_number + 32400 * (check_pos(val) - 1) + ((i * 90 + j) * 4);
				color = Xil_In32(color_addr);
			}
			Xil_Out32(TFT_FRAME_ADDR0 + addr, color);
		}
	return;
}

void display_score(int val){
	int digits[6] = {0, 0, 0, 0, 0, 0};
	for (int i = 5; i >= 0; i--){
		digits[i] = val % 10;
		val /= 10;
	}
	for (int i = 0; i < 6; i++){
		int pos_row_start = 150 , pos_col_start = 5 + i * 25;
			for (int row = 0; row < 40; row++)
				for (int col = 0; col < 25; ++col){
					u32 color = Xil_In32((unsigned int)gImage_digits + 4000 * digits[i] + ((row * 25 + col) * 4));
					Xil_Out32(TFT_FRAME_ADDR0 + 4 * (1024 * (row + pos_row_start) + (col + 470 + pos_col_start)), color);
				}
	}

}

void display_outcomes(){
	for (int i = 0; i < 16; i++) display_bulk(i, maps[i / 4][i % 4]);
}


void display_message(int occassion) {
	if (occassion == 0) {
		for (int row = 300; row < 325; row++)
			for (int col = 480; col < 480 + 90; col++) {
				u32 color = Xil_In32((unsigned int)gImage_over + (90 * (row - 300) + (col - 480)) * 4);
				Xil_Out32(TFT_FRAME_ADDR0 + 4 * (row * 1024 + col), color);
			}
	} else {
		for (int row = 0; row < 24; row++)
			for (int col = 0; col < 90; col++) {
				u32 color = Xil_In32((unsigned int)gImage_win + ((90 * row + col) * 4));
				Xil_Out32(TFT_FRAME_ADDR0 + 4 * ((row + 300) * 1024 + col + 480), color);
			}
	}
}
