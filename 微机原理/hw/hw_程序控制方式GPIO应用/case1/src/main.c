/*
 * main.c
 *  Created on: 2023��4��13��
 *      Author: ������
 * ʵʱ��ȡ16λ���ص�״̬������ʱ��ӳ��16λLED��Ӧλ�ϣ�ͬʱ��16λ���ض�Ӧ��4λʮ���������ִӸߵ���������ʾ��8λ�߶�����ܵ�λ5~λ8�ϣ������������
 */


#include "xgpio_l.h"
#include "xparameters.h"
#include "xil_io.h"

unsigned char segs[16] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
					0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};


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

int main(){

	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI_OFFSET, 0x0000ffff);
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI2_OFFSET, 0x00);
	while(1) {
		unsigned int data = Xil_In16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA_OFFSET);		// read the data from the switches.
		Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA_OFFSET, data << 16);
		display_segs(data & 0xffff);
	}
	return 0;
}
