#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
int n, tmp[1100][1100], pown;
void init(int x1, int y1, int x2, int y2, int c) {
	if(x1 == x2 && y1 == y2)
		tmp[x1][y1]= c;
	else if(c) {
		for(int i= x1; i <= x2; i++)
			for(int j= y1; j <= y2; j++) tmp[i][j]= 1;
	}
	else {
		int midx= (x1 + x2) / 2, midy= (y1 + y2) / 2;
		init(x1, y1, midx, midy, 1);
		init(x1, midy + 1, midx, y2, 0);
		init(midx + 1, y1, x2, midy, 0);
		init(midx + 1, midy + 1, x2, y2, 0);
	}
	return;
}
int main() {
	cin >> n, pown= pow(2, n);
	init(1, 1, pown, pown, 0);
	for(int i= 1; i <= pown; i++) {
		for(int j= 1; j <= pown; j++) putchar('0' + (tmp[i][j] ^ 1)), putchar(' ');
		putchar('\n');
	}
	return 0;
}