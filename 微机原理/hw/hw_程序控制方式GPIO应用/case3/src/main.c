/*
 * main.c
 *
 *  Created on: 2023年4月13日
 *      Author: 杨筠松
 *  实时获取16位开关的状态，并将16位开关分为高13位（SW15~3）、低3位（SW2~0）两部分，
 *  要求将SW15~3 13位无符号二进制数（D12~0）表示的十进制数显示在8位七段数码管上，
 *  且最高位从SW2~0（1≤SW2~0≤5）所指示位置开始显示，无数据数码管灭。
 *  即若SW15~0=0xfff9，结果如图所示
 */


#include "xgpio_l.h"
#include "xparameters.h"
#include "xil_io.h"

unsigned char segs[16] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
					0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};


void display_segs(unsigned short data, unsigned short pos_in) {

	unsigned short pos;
	switch (pos_in) {
		case 5:
			pos = 0xfe;
			break;
		case 4:
			pos = 0xfd;
			break;
		case 3:
			pos = 0xfb;
			break;
		case 2:
			pos = 0xf7;
			break;
		case 1:
			pos = 0xef;
			break;
		default:
			pos = 0xff;
			break;
	}

	unsigned short tmp = data;
	int i = 0;
	unsigned char tmp_out[4] = {0, 0, 0, 0};
	for (i = 0; i < 4; i++){
		tmp_out[i] = segs[tmp & 0xf] & 0xff;
		tmp >>= 4;
	}
	for (i = 3; i >= 0; i--) {
		Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA2_OFFSET,
							((pos & 0xff) << 8) + tmp_out[i]);
		pos = (pos << 1) + 1;
		unsigned int times = 0;
		for (times = 0; times <= 1000; times++);
	}

}
int main(){
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI_OFFSET, 0x0000ffff);
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI2_OFFSET, 0x0000);
	while(1) {
		unsigned short data = Xil_In16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA_OFFSET);		// read the data from the switches.
		Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA_OFFSET, data << 16);
		unsigned short switch_data = (data >> 3) & 0x1fff, switch_pos = data & 0x7;

		unsigned short data_out = 0;
		while (switch_data) {
			data_out <<= 4;
			data_out += switch_data % 10;
			switch_data = switch_data / 10;
		}

		display_segs(data_out, switch_pos);
	}
	return 0;

}
