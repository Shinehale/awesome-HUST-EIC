/*
 * logic.h
 *
 *  Created on: 2023��5��6��
 *      Author: ������
 */


#ifndef SRC_LOGIC_H_
#define SRC_LOGIC_H_

void init_game(void);
void move_forward(int);
void generate_new(void);


// function for checkout the outcome
int check_win(void);
int check_lose(void);


#endif /* SRC_LOGIC_H_ */
