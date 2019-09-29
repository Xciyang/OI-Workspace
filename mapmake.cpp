#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
#define MAPX 100
#define MAPY 100
int mapx[MAPY][MAPX];
int main() {
	for(int i= 0; i < 50; i++) {
		LineDDA(rand() % MAPX, rand() % MAPY, rand() % MAPX, rand() % MAPY, [](int x, int y, LPARAM) { mapx[y][x]= 1; }, 0);
	}
	freopen("a.txt", "w", stdout);
	for(int i= 0; i < MAPY; i++) {
		for(int j= 0; j < MAPX; j++) {
			printf("%d ", mapx[i][j]);
		}
		putchar('\n');
	}

	return 0;
}
