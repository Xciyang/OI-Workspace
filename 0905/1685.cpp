#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
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
int n, m, sc[100][100], s[100][100], bestans;
int moves[4][2]= {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
struct BJ {
	int x, y, sco;
	int operator<(const BJ &b2) const {
		return sco < b2.sco;
	}
} tmpb[100];
void dfs(int nx, int ny, int step) {
	int cnt= 0, cnt2= 0;
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) {
			if(s[i][j])
				cnt+= s[i][j] * sc[i][j];
			else
				tmpb[++cnt2]= BJ{i, j, sc[i][j]};
		}
	}
	bestans= max(bestans, cnt);
	sort(tmpb + 1, tmpb + cnt2 + 1);
	for(int i= step; i <= m * n; i++) cnt+= i * tmpb[i - step + 1].sco;
	if(cnt <= bestans) return;
	cnt= 0;
	BJ beg[20];
	if(nx == 1 || nx == n || ny == 1 || ny == m) {
		for(int i= 1; i <= n; i++)
			for(int j= 1; j <= m; j++)
				if(i == 1 || i == n || j == 1 || j == m)
					if(!s[i][j]) beg[++cnt]= BJ{i, j, sc[i][j]};
	}
	int newx, newy;
	for(int i= 0; i < 4; i++) {
		newx= nx + moves[i][0], newy= ny + moves[i][1];
		if(newx < 1 || newx > n || newy < 1 || newy > m || s[newx][newy]) continue;
		beg[++cnt]= BJ{newx, newy, sc[newx][newy]};
	}
	if(cnt) {
		sort(beg + 1, beg + cnt + 1);
		for(int i= 1; i <= cnt; i++) s[beg[i].x][beg[i].y]= step, dfs(beg[i].x, beg[i].y, step + 1), s[beg[i].x][beg[i].y]= 0;
	}
	return;
}
int main() {
	n= read(), m= read();
	int cnt= 0;
	BJ beg[20];
	for(int i= 1; i <= n; i++)
		for(int j= 1; j <= m; j++) {
			sc[i][j]= read();
			if(i == 1 || i == n || j == 1 || j == m) beg[++cnt]= BJ{i, j, sc[i][j]};
		}
	sort(beg + 1, beg + cnt + 1);
	for(int i= 1; i <= cnt; i++) s[beg[i].x][beg[i].y]= 1, dfs(beg[i].x, beg[i].y, 2), s[beg[i].x][beg[i].y]= 0;
	printf("%d\n", bestans);
	return 0;
}