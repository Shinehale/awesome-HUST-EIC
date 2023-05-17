/*
 * logic.c
 *
 *  Created on: 2023ƒÍ5‘¬6»’
 *      Author: —ÓÛﬁÀ…
 */


#include "logic.h"
#include "stdio.h"
#include "stdlib.h"
#include "display.h"

extern unsigned int maps[4][4];

int total_score = 0;
int directions[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};


void init_game(void) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			maps[i][j] = 0;
	total_score = 0;
	generate_new();
}

void generate_new(){
	int pos_empty[16], cnt = 0;
	for (int i = 0; i < 16; i++)
		if (maps[i / 4][i % 4] == 0) {
			pos_empty[cnt] = i;
			cnt++;
		}
	srand(rand());
	xil_printf("random :%d\n", cnt);
	int select_pos = pos_empty[rand() % cnt];
	maps[select_pos / 4][select_pos % 4] = 2;
	xil_printf("random :%d  %d\n", select_pos / 4, select_pos % 4);
	display_outcomes();
}

void move_forward(int id){
	if (id == 1) {
		for (int col = 0; col < 4; col++) {
			int ans[4] = {0}, cnt = 0, lst = -1;
			for (int i = 0; i < 4; i++) {
				if (maps[i][col] == 0) continue;
				if (lst == -1)  {
					ans[cnt++] = maps[i][col];
					lst = i;
				} else if (maps[i][col] == maps[lst][col]){
					ans[cnt - 1] *= 2;
					total_score += ans[cnt - 1];
					lst = -1;
				} else {
					ans[cnt++] = maps[i][col];
					lst = i;
				}
			}
			for (int i = 0; i < 4; i++)
				maps[i][col] = ans[i];
		}
		display_score(total_score);
		generate_new();
	} else if (id == 2) {
		for (int col = 0; col < 4; col++) {
			int ans[4] = {0}, cnt = 3, lst = -1;
			for (int i = 3; i >= 0; i--) {
				if (maps[i][col] == 0) continue;
				if (lst == -1)  {
					ans[cnt--] = maps[i][col];
					lst = i;
				} else if (maps[i][col] == maps[lst][col]){
					ans[cnt + 1] *= 2;
					total_score += ans[cnt + 1];
					lst = -1;
				} else {
					ans[cnt--] = maps[i][col];
					lst = i;
				}
			}
			for (int i = 3; i >= 0; i--)
				maps[i][col] = ans[i];
		}
		display_score(total_score);
		generate_new();
	} else if (id == 3){
		for (int row = 0; row < 4; row++) {
			int ans[4] = {0}, cnt = 0, lst = -1;
			for (int i = 0; i < 4; i++) {
				if (maps[row][i] == 0) continue;
				if (lst == -1)  {
					ans[cnt++] = maps[row][i];
					lst = i;
				} else if (maps[row][i] == maps[row][lst]){
					ans[cnt - 1] *= 2;
					total_score += ans[cnt - 1];
					lst = -1;
				} else {
					ans[cnt++] = maps[row][i];
					lst = i;
				}
			}
			for (int i = 0; i < 4; i++)
				maps[row][i] = ans[i];
		}
		display_score(total_score);
		generate_new();
	} else if (id == 4) {
		for (int row = 0; row < 4; row++) {
			int ans[4] = {0}, cnt = 3, lst = -1;
			for (int i = 3; i >= 0; i--) {
				if (maps[row][i] == 0) continue;
				if (lst == -1)  {
					ans[cnt--] = maps[row][i];
					lst = i;
				} else if (maps[row][i] == maps[row][lst]){
					ans[cnt + 1] *= 2;
					total_score += ans[cnt + 1];
					lst = -1;
				} else {
					ans[cnt--] = maps[row][i];
					lst = i;
				}
			}
			for (int i = 3; i >= 0; i--)
				maps[row][i] = ans[i];
		}
		display_score(total_score);
		generate_new();
	}

	if (check_lose()) display_message(0);
	if (check_win()) display_message(1);

}
int check_lose(void){
//	for (int col = 0; col < 4; col++) if (maps[0][col] == 0) return 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++){
			if (maps[i][j]) {
				for (int k = 0; k < 4; k++){
					int new_x = i + directions[k][0], new_y = j + directions[k][1];
					if (new_x < 0 || new_x > 3 || new_y < 0 || new_y > 3) continue;
					if (maps[new_x][new_y] == maps[i][j]) return 0;
				}
			} else return 0;
		}
	return 1;
}

int check_win(void) {
	/**
	 * check whether the maps are full or has encountered 2048
	 * if the answer is yes, return 1
	 * else return 0.
	 */
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++){
			if (maps[i][j] == 256) return 1;
		}
	return 0;
}

