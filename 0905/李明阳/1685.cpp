#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
inline int read() {
	int e= 0, f= 1;
	char ch= getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') e= e * 10 + ch - '0', ch= getchar();
	return e * f;
}
int n, m, sc[100][100], bestans;
int moves[4][2]= {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
void dfs(int, int, int, int);
void dfs2(int step, int score) {
	int j= -1;
	for(int i= 1; i <= n; i++) {
		if(sc[i][1] != -1) {
			j= sc[i][1], sc[i][1]= -1;
			dfs(1, i, score + step * j, step + 1);
			sc[i][1]= j;
		}
		if(m != 1 && sc[i][m] != -1) {
			j= sc[i][m], sc[i][m]= -1;
			dfs(1, i, score + step * j, step + 1);
			sc[i][m]= j;
		}
	}
	for(int i= 2, j; i < m; i++) {
		if(sc[1][i] != -1) {
			j= sc[1][i], sc[1][i]= -1;
			dfs(1, i, score + step * j, step + 1);
			sc[1][i]= j;
		}
		if(n != 1 && sc[n][i] != -1) {
			j= sc[n][i], sc[n][i]= -1;
			dfs(1, i, score + step * j, step + 1);
			sc[n][i]= j;
		}
	}
	if(j == -1) bestans= max(bestans, score);
	return;
}
void dfs(int nx, int ny, int score, int step) {
	register int newx, newy, j= -1;
	for(int i= 0; i < 4; i++) {
		newx= nx + moves[i][0], newy= ny + moves[i][1];
		if(newx < 1 || newx > n || newy < 1 || newy > m) {
			dfs2(step, score), j= 0;
			continue;
		}
		if(sc[newx][newy] == -1) continue;
		j= sc[newx][newy], sc[newx][newy]= -1;
		dfs(newx, newy, score + step * j, step + 1);
		sc[newx][newy]= j;
	}
	if(j == -1) bestans= max(bestans, score);
	return;
}
int main() {
	n= read(), m= read();
	for(int i= 1; i <= n; i++)
		for(int j= 1; j <= m; j++) sc[i][j]= read();
	dfs2(1, 0);
	printf("%d\n", bestans);
	return 0;
}