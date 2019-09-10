#include <iostream>
#include <stdio.h>
using namespace std;
int n, ope[7], clo[7], c, tmpx, flag;
const int res[][7]= {
	{0, 1, 1, 1, 1, 1, 1},  // - | 1 1 | 4 4 | 1 2 3
	{0, 0, 0, 0, 0, 0, 0},  // 1 | 2 3
	{0, 0, 1, 0, 1, 0, 1},  // 2 | 1 3
	{0, 1, 0, 1, 0, 1, 0},  // 3 | 1 2
	{0, 0, 1, 1, 0, 1, 1},  // 4 | 1 1 4 | 1 2 3 4
	{0, 1, 0, 0, 1, 0, 0},  // 1 4 | 2 3 4
	{0, 1, 1, 0, 0, 0, 1},  // 2 4 | 1 3 4
	{0, 0, 0, 1, 1, 1, 0},  // 3 4 | 1 2 4
};
const int sortres[][7]= {
	{0, 0, 0, 0, 0, 0, 0},  // 1 | 2 3
	{0, 0, 0, 1, 1, 1, 0},  // 3 4 | 1 2 4
	{0, 0, 1, 0, 1, 0, 1},  // 2 | 1 3
	{0, 0, 1, 1, 0, 1, 1},  // 4 | 1 1 4 | 1 2 3 4
	{0, 1, 0, 0, 1, 0, 0},  // 1 4 | 2 3 4
	{0, 1, 0, 1, 0, 1, 0},  // 3 | 1 2
	{0, 1, 1, 0, 0, 0, 1},  // 2 4 | 1 3 4
	{0, 1, 1, 1, 1, 1, 1},  // - | 1 1 | 4 4 | 1 2 3
};
int main() {
	cin >> n >> c;
	while(true) {
		cin >> tmpx;
		if(tmpx == -1) break;
		ope[(tmpx - 1) % 6 + 1]= 1;
	}
	while(true) {
		cin >> tmpx;
		if(tmpx == -1) break;
		clo[(tmpx - 1) % 6 + 1]= 1;
	}
	if(c == 0) {
		for(int i= 1; i <= 6; i++)
			if(clo[i]) return printf("IMPOSSIBLE\n"), 0;
		for(int i= 1; i <= n; i++) putchar('0' + sortres[7][(i - 1) % 6 + 1]);
		return putchar('\n'), 0;
	}
	if(c == 1) {
		for(int k= 0; k < 8; k++) {
			if(k == 1 || k == 4 || k == 6 || k == 7) continue;
			for(int i= 1; i <= 6; i++)
				if((sortres[k][i] && clo[i]) || (!sortres[k][i] && ope[i])) goto nxt1;
			for(int i= 1; i <= n; i++) putchar('0' + sortres[k][(i - 1) % 6 + 1]);
			putchar('\n'), flag= 1;
		nxt1:;
		}
	}
	else if(c == 2) {
		for(int k= 0; k < 8; k++) {
			if(k == 3) continue;
			for(int i= 1; i <= 6; i++)
				if((sortres[k][i] && clo[i]) || (!sortres[k][i] && ope[i])) goto nxt2;
			for(int i= 1; i <= n; i++) putchar('0' + sortres[k][(i - 1) % 6 + 1]);
			putchar('\n'), flag= 1;
		nxt2:;
		}
	}
	else {
		for(int k= 0; k < 8; k++) {
			for(int i= 1; i <= 6; i++)
				if((sortres[k][i] && clo[i]) || (!sortres[k][i] && ope[i])) goto nxt3;
			for(int i= 1; i <= n; i++) putchar('0' + sortres[k][(i - 1) % 6 + 1]);
			putchar('\n'), flag= 1;
		nxt3:;
		}
	}
	if(!flag) printf("IMPOSSIBLE\n");
	return 0;
}