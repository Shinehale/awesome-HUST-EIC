/*
 * main.c
 *
 *  Created on: 2023��4��13��
 *      Author: ������
 *  ʵʱ��ȡ16λ���ص�״̬������16λ���ط�Ϊ��8λ����8λ���ֱ�������8λ�������������ǵĺ͡�����������ֱ������16λLED�ĸ�8λ����8λ��
 *  ͬʱ���͡����Ӧ��2λʮ���������ֱַ������8λ�߶�����ܵ�λ3~λ4��λ7~λ8�ϣ������������
 */


#include "xgpio_l.h"
#include "xparameters.h"
#include "xil_io.h"

unsigned char segs[16] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
					0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};


void display_segs(unsigned short data) {
	unsigned short pos = 0xffbf, i = 0, tmp = data;
	for (i = 0; i < 2; i++){
		Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA2_OFFSET,
					((pos & 0xff) << 8) + (segs[tmp & 0xf] & 0xff));
		tmp >>= 4;
		pos = (pos << 1) + 1;
		unsigned int times = 0;
		for (times = 0; times <= 1000; times++);
	}
	pos =  0xfffb;
	for (i = 0; i < 2; i++){
		Xil_Out16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA2_OFFSET,
					((pos & 0xff) << 8) + (segs[tmp & 0xf] & 0xff));
		tmp >>= 4;
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
		unsigned short data_high = data >> 8 & 0xff, data_low = data & 0xff;
		unsigned short data_sum = data_high + data_low, data_minus = (data_high + ((~data_low + 1) & 0xff)) & 0xff;

		unsigned short data_out = (data_sum << 8) + data_minus;
		display_segs(data_out & 0xffff);
	}
	return 0;
}
