/*
 * main.c
 *
 *  Created on: 2023.4.23
 *      Author: Shine_hale
 *  �����ֳɵĽӿڵ�·��ʵ��һ�¹��ܣ�
 *  1. 16��LED������ѭ��������ѭ���ٶȿ�ͨ���������������������п��ƣ�����һ����ťÿ��һ�β������٣���һ������ÿ��һ�β�������
 *  2. 4���߶������ʵʱ��ʾ16���������ر�ʾ��ʮ��������
 */


#include "xintc_l.h"
#include "xtmrctr_l.h"
#include "xgpio_l.h"
#include "xparameters.h"
#include "xio.h"
#include "xil_exception.h"

unsigned char segs[16] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
					0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};
unsigned int paces[5] = {4000000, 2000000, 1000000, 500000, 250000};

void main_part(void);
void display_segs(unsigned short);
int main(){
	Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI_OFFSET, 0xffff); 		// set SW as input
	Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI2_OFFSET, 0x0);			// set LED as output
	Xil_Out16(XPAR_AXI_GPIO_2_BASEADDR + XGPIO_TRI_OFFSET, 0xffff);			// set BTND, U, L, R, C as input
	Xil_Out32(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_TRI_OFFSET, 0x0);
	Xil_Out32(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_TRI2_OFFSET, 0x0);

	main_part();

	return 0;
}
unsigned short last_button = 0, led_pos = 0x1, pace_pos = 0;
unsigned int led_timer = 0;
void main_part(void){
	while(1) {
		unsigned short SW = Xil_In16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA_OFFSET);
		unsigned short now_button = Xil_In16(XPAR_AXI_GPIO_2_BASEADDR + XGPIO_DATA_OFFSET);
		if (now_button != last_button) {
			last_button = now_button;
			if ((now_button & 0x2) == 0x2) {
				if (pace_pos < 4) pace_pos += 1;
				xil_printf("%d", pace_pos);
			}
			if ((now_button & 0x10) == 0x10) {
				if (pace_pos > 0) pace_pos -= 1;
			}
		}
		display_segs(SW);
		if (led_timer > paces[pace_pos]) {
			led_timer = 0;
			led_pos = (led_pos << 1);
			if (led_pos == 0x8000) led_pos = 0x1;
			Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA2_OFFSET, led_pos);
		}
	}
}
void display_segs(unsigned short data) {
	unsigned short pos = 0xfe, i = 0;
	for (i = 0; i < 4; i++){
		Xil_Out8(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_DATA_OFFSET, pos & 0xff);
		Xil_Out8(XPAR_AXI_GPIO_1_BASEADDR + XGPIO_DATA2_OFFSET, segs[data & 0xf]);
		data >>= 4;
		pos = (pos << 1) + 1;
		unsigned int times = 0;
		for (times = 0; times <= 1000; times++) led_timer++;
	}
}
