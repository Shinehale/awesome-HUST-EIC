/*
 * display.h
 *
 *  Created on: 2023ƒÍ5‘¬6»’
 *      Author: —ÓÛﬁÀ…
 */

#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_

#define TFT_FRAME_ADDR0 XPAR_MIG7SERIES_0_HIGHADDR - 0x001fffff
#define TFT_AR_OFFSET 0x0
#define TFT_0_BASEADDR 0x44a00000

void init_display(void);
void display_bulk(int, int);
void display_score(int);
void display_message(int);
#endif /* SRC_DISPLAY_H_ */
