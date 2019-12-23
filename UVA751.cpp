#include <iostream>
#include <stdio.h>
using namespace std;
int edg[11][11];
int tri[] = {(1 << 0) + (1 << 1) + (1 << 2),
			 (1 << 3) + (1 << 4) + (1 << 7),
			 (1 << 2) + (1 << 4) + (1 << 5),
			 (1 << 5) + (1 << 6) + (1 << 10),
			 (1 << 8) + (1 << 9) + (1 << 15),
			 (1 << 7) + (1 << 9) + (1 << 11),
			 (1 << 11) + (1 << 12) + (1 << 16),
			 (1 << 10) + (1 << 12) + (1 << 13),
			 (1 << 13) + (1 << 14) + (1 << 17)};
#define addedge(x, y, z) (edg[x][y] = edg[y][x] = z)

const int full = (1 << 18) - 1;
int mm[full + 1];

void init() {
	addedge(1, 2, 0);
	addedge(1, 3, 1);
	addedge(2, 3, 2);
	addedge(2, 4, 3);
	addedge(2, 5, 4);
	addedge(3, 5, 5);
	addedge(3, 6, 6);
	addedge(4, 5, 7);
	addedge(4, 7, 8);
	addedge(4, 8, 9);
	addedge(5, 6, 10);
	addedge(5, 8, 11);
	addedge(5, 9, 12);
	addedge(6, 9, 13);
	addedge(6, 10, 14);
	addedge(7, 8, 15);
	addedge(8, 9, 16);
	addedge(9, 10, 17);
	for(int i = 0; i < full; i++) mm[i] = -0x3f3f3f3f;
	mm[full] = 0;
	return;
}
int T, n, tmpx, tmpy;
int nextStep(int lst, int nst) {
	int cnt = 0;
	for(int i = 0; i < 9; i++)
		if((lst & tri[i]) != tri[i] && (nst & tri[i]) == tri[i]) ++cnt;
	return cnt;
}

int max_min(int nowp, int st) {
	if(mm[st] != -0x3f3f3f3f) return mm[st];
	int fst = full ^ st, nst, maxx = -0x3f3f3f3f;
	while(fst) {
		int edge = fst & (-fst);
		int res = nextStep(st, (nst = st | edge));
		if(res) {
			maxx = max(maxx, res + max_min(nowp, nst));
		}
		else {
			maxx = max(maxx, -max_min(nowp ^ 1, nst));
		}
		fst -= edge;
	}
	return mm[st] = maxx;
}
int main() {
	init();
	cin >> T;
	for(int t = 1; t <= T; t++) {
		cin >> n;
		int st = 0, p = 0, ans[2] = {0};
		for(int i = 1; i <= n; i++) {
			cin >> tmpx >> tmpy;
			int res = nextStep(st, st | (1 << edg[tmpx][tmpy]));
			st = st | (1 << edg[tmpx][tmpy]);
			if(res) {
				ans[p] += res;
			}
			else {
				p ^= 1;
			}
		}
		int res = max_min(p, st);
		cout << "Game " << t << ": ";
		if((ans[p] + res > ans[p ^ 1]) ^ p) {
			cout << "A wins." << endl;
		}
		else {
			cout << "B wins." << endl;
		}
	}
	return 0;
}