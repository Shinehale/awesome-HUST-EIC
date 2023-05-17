/*
 * main.c
 *
 *  Created on: 2023.4.19
 *      Author: Shine_hale
 *  ʵʱ��ȡ16λ���ص�״̬������16λ���ط�Ϊ��13λ��SW15~3������3λ��SW2~0�������֣�
 *  Ҫ��SW15~3 13λ�޷��Ŷ���������D12~0����ʾ��ʮ��������ʾ��8λ�߶�������ϣ�
 *  �����λ��SW2~0��1��SW2~0��5����ָʾλ�ÿ�ʼ��ʾ���������������
 *  ����SW15~0=0xfff9�������ͼ��ʾ
 */


#include "xgpio_l.h"
#include "xparameters.h"
#include "xil_io.h"
#include "xil_exception.h"
#include "xintc_l.h"
#include "xtmrctr_l.h"

unsigned char segs[16] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
					0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};

void setup_GPIO_interrupt(void);
void General_handler(void) __attribute__((interrupt_handler));
void display_segs(unsigned short, unsigned short);

unsigned short data_out = 0;
unsigned short pos_out = 0;

int main(){

	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI_OFFSET, 0x0000ffff);
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_TRI2_OFFSET, 0x00);
	setup_GPIO_interrupt();
	while (1){
		display_segs(data_out & 0xffff, pos_out);
	}
	return 0;
}

void setup_GPIO_interrupt(void) {

	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IAR_OFFSET, XPAR_AXI_GPIO_0_IP2INTC_IRPT_MASK);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IER_OFFSET, XPAR_AXI_GPIO_0_IP2INTC_IRPT_MASK);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_MER_OFFSET, XIN_INT_MASTER_ENABLE_MASK | XIN_INT_HARDWARE_ENABLE_MASK);

	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_IER_OFFSET, XGPIO_IR_CH1_MASK);		//enable the channel 1 interrupt
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_ISR_OFFSET, XGPIO_IR_CH1_MASK);		//clear the channel 1 interrupt status
	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_GIE_OFFSET, XGPIO_GIE_GINTR_ENABLE_MASK);	//enable GPIO interrupt and output

	microblaze_enable_interrupts();
}

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

void General_handler(void){

	unsigned short SW_status = Xil_In16(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA_OFFSET);		// read the data from the switches.
	unsigned short switch_data = (SW_status >> 3) & 0x1fff;
	unsigned data = 0;
	while (switch_data) {
		data <<= 4;
		data += switch_data % 10;
		switch_data = switch_data / 10;
	}
	data_out = data;
	pos_out = SW_status & 0x7;

	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + XGPIO_DATA_OFFSET, SW_status << 16);
	Xil_Out32(XPAR_GPIO_0_BASEADDR + XGPIO_ISR_OFFSET, XGPIO_IR_CH1_MASK);
	Xil_Out32(XPAR_INTC_0_BASEADDR + XIN_IAR_OFFSET, XGPIO_IR_CH1_MASK);

}

