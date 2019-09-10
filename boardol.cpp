#include <iostream>
#include <stdio.h>
using namespace std;
#define BMAX 19
int BOARD[20][20], NEWBOARD[20][20];
int MOVES[4][2]= {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
inline int abs(int x) {
	return x < 0 ? -x : x;
}
inline int addToZero(int x) {
	return x > 0 ? -1 : 1;
}
void nextStep() {
	for(int i= 1; i <= BMAX; i++) 
		for(int j= 1; j <= BMAX; j++) NEWBOARD[i][j]= BOARD[i][j];
	for(int i= 1; i <= BMAX; i++) {
		for(int j= 1; j <= BMAX; j++) {
			if(!BOARD[i][j]) continue;
			for(int k= 0; k < 4; k++) {
				int ii= i + MOVES[k][0], jj= j + MOVES[k][1];
				if(ii < 1 || ii > BMAX || jj < 1 || j > BMAX || !BOARD[i][j]) continue;
				if(BOARD[i][j] * BOARD[ii][jj] < 0 && abs(BOARD[ii][jj]) >= abs(BOARD[i][j]) && NEWBOARD[i][j] != 0) NEWBOARD[i][j]+= addToZero(NEWBOARD[i][j]);
			}
		}
	}
	for(int i= 1; i <= BMAX; i++) 
		for(int j= 1; j <= BMAX; j++) BOARD[i][j]= NEWBOARD[i][j];
	return;
}
int main() {
	BOARD[9][9] = BOARD[10][10] = 4;
	BOARD[9][10] = BOARD[10][9] = -4;
	int times= 10;
	while(times--) {
		for(int i= 1; i <= BMAX; i++) {
			for(int j= 1; j <= BMAX; j++) {
				printf("%02d ", BOARD[i][j]);
			}
			printf("\n");
		}
		nextStep();
	}
	return 0;
}
