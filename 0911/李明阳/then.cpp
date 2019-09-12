#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#define file(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)
using namespace std;
template < typename T >
inline void read(T &e) {
	e= 0;
	T f= 1;
	char ch= getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') e= e * 10 + ch - '0', ch= getchar();
	e*= f;
	return;
}
template < typename T >
inline int put(const T &e) {
	if(e < 0) return putchar('-'), put(-e);
	if(e > 9) put(e / 10);
	return putchar('0' + e % 10);
}
int t, R, C, n, b[105][105], tmpx, tmpy, tmpz, newx[3], newy[3], wp[105][105];
queue< int > qx, qy;
int moves[][2]= {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};
int movess[][3]= {{7, 0, 1}, {1, 2, 3}, {3, 4, 5}, {5, 6, 7}};
int inMap(int x, int y) {
	return !(x < 1 || x > R || y < 1 || y > C);
}
int main() {
    file("then");
	read(t);
	while(t--) {
		read(R), read(C), read(n);
		for(int i= 1; i <= R; i++)
			for(int j= 1; j <= C; j++) b[i][j]= -1, wp[i][j]= 0;
		for(int i= 1; i <= n; i++) {
			read(tmpx), read(tmpy), read(tmpz);
			b[tmpx][tmpy]= tmpz;
			if(tmpz < 0) goto failed;
		}
		for(int i= 1; i <= R; i++)
			for(int j= 1; j <= C; j++) qx.push(i), qy.push(j), wp[i][j]= 1;
		while(!qx.empty()) {
			tmpx= qx.front(), tmpy= qy.front(), qx.pop(), qy.pop();
			if(b[tmpx][tmpy] != -1) {
				for(int i= 0, cnt; i < 4; i++) {
					cnt= 0;
					for(int j= 0; j < 3; j++) {
						newx[j]= tmpx + moves[movess[i][j]][0], newy[j]= tmpy + moves[movess[i][j]][1];
						if(inMap(newx[j], newy[j]) && b[newx[j]][newy[j]] != -1) ++cnt;
					}
					if(cnt == 3 && b[tmpx][tmpy] != b[newx[0]][newy[0]] + b[newx[2]][newy[2]] - b[newx[1]][newy[1]]) goto failed;
				}
				continue;
			}
			int ans= -1;
			for(int i= 0, cnt; i < 4; i++) {
				cnt= 0;
				for(int j= 0; j < 3; j++) {
					newx[j]= tmpx + moves[movess[i][j]][0], newy[j]= tmpy + moves[movess[i][j]][1];
					if(inMap(newx[j], newy[j]) && b[newx[j]][newy[j]] != -1) ++cnt;
				}
				if(cnt == 3) {
					if(ans == -1) {
						ans= b[newx[0]][newy[0]] + b[newx[2]][newy[2]] - b[newx[1]][newy[1]];
						if(ans < 0) goto failed;
					}
					else if(ans != b[newx[0]][newy[0]] + b[newx[2]][newy[2]] - b[newx[1]][newy[1]])
						goto failed;
				}
			}
			if(ans == -1) {
				wp[tmpx][tmpy]= 0;
				continue;
			}
			for(int i= 0, cnt, wh; i < 4; i++) {
				cnt= 0;
				for(int j= 0; j < 3; j++) {
					newx[j]= tmpx + moves[movess[i][j]][0], newy[j]= tmpy + moves[movess[i][j]][1];
					if(!inMap(newx[j], newy[j])) {
						cnt= 0;
						break;
					}
					if(b[newx[j]][newy[j]] != -1)
						++cnt;
					else
						wh= j;
				}
				if(cnt == 2 && !wp[newx[wh]][newy[wh]]) wp[newx[wh]][newy[wh]]= 1, qx.push(newx[wh]), qy.push(newy[wh]);
			}
		}
		cout << "Yes" << endl;
		if(0) {
		failed:
			cout << "No" << endl;
		}
	}
	return 0;
}