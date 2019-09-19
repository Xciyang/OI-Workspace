#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <queue>
#include <algorithm>
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
int n, m, a[305][305], ans[305][305], cnt;
int maxx[305][305], wp[305][305], c[305][305], wptr;
struct NODE {
	int x, y;
	inline int operator>(const NODE &n2) const {
		return a[x][y] > a[n2.x][n2.y];
	}
	inline int operator<(const NODE &n2) const {
		return a[x][y] < a[n2.x][n2.y];
	}
} ks[93025];
queue< NODE > qu;
int moves[4][2]= {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
void BFS1(int bx, int by) {
	while(!qu.empty()) qu.pop();
	qu.push(NODE{bx, by}), wp[bx][by]= wptr;
	register NODE nown, nxt;
	while(!qu.empty()) {
		nown= qu.front(), qu.pop();
		if(nown.x == 0 || nown.x == n + 1 || nown.y == 0 || nown.y == m + 1) {
			c[bx][by]= 1;
			return;
		}
		for(register int i= 0; i < 4; i++) {
			nxt.x= nown.x + moves[i][0], nxt.y= nown.y + moves[i][1];
			if(a[nxt.x][nxt.y] <= a[nown.x][nown.y]) {
				if(wp[nxt.x][nxt.y] == wptr) continue;
				if(c[nxt.x][nxt.y]) {
					c[bx][by]= 1;
					return;
				}
				wp[nxt.x][nxt.y]= wptr, qu.push(nxt);
			}
		}
	}
	return;
}
void BFS2(int bx, int by) {
	NODE nown= NODE{bx, by}, nxt;
    int res= 0x3f3f3f3f;
	for(register int i= 0; i < 4; i++) {
		nxt.x= nown.x + moves[i][0], nxt.y= nown.y + moves[i][1];
		if(a[nxt.x][nxt.y] > a[nown.x][nown.y]) {
			res= min(res, maxx[nxt.x][nxt.y]);
		}
	}
    maxx[bx][by]= max(a[bx][by], res);
	return;
}
int main() {
	read(n), read(m);
	for(register int i= 1; i <= n; i++)
		for(register int j= 1; j <= m; j++) read(a[i][j]), maxx[i][j]= a[i][j];
	for(register int i= 1; i <= n; i++)
		for(register int j= 1; j <= m; j++) ks[++cnt].x= i, ks[cnt].y= j;
	sort(ks + 1, ks + n + 1);
	for(int i= 1; i <= cnt; i++) ++wptr, BFS1(ks[i].x, ks[i].y);
	sort(ks + 1, ks + n + 1, greater< NODE >());
	for(int i= 1; i <= cnt; i++)
		if(!c[ks[i].x][ks[i].y]) BFS2(ks[i].x, ks[i].y);
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) put(c[i][j] ? 0 : maxx[i][j] - a[i][j]), putchar(' ');
		putchar('\n');
	}
	return 0;
}
/*
6 6
6 6 6 6 6 6
6 5 5 5 5 6
6 5 4 4 5 6
6 5 4 4 5 6
6 5 5 5 5 6
6 6 6 6 6 6
*/
/*
	for(int i= 1; i <= n; i++)
		for(int j= 1; j <= m; j++) read(a[i][j]);
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) f[0][i][j]= max(f[0][i][j - 1], a[i][j]);
		for(int j= m; j; j--) f[1][i][j]= max(f[1][i][j + 1], a[i][j]);
	}
	for(int j= 1; j <= m; j++) {
		for(int i= 1; i <= n; i++) f[2][i][j]= max(f[2][i - 1][j], a[i][j]);
		for(int i= n; i; i--) f[3][i][j]= max(f[3][i + 1][j], a[i][j]);
	}
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) {
			int minx= 1e9;
			for(int k= 0; k < 4; k++) minx= min(minx, f[k][i][j]);
			ans[i][j]= max(0, minx - a[i][j]);
			put(ans[i][j]), putchar(' ');
		}
		putchar('\n');
	}
*/