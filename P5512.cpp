#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;
int n, m;
int flag[201], canc[101][101], canf[101][101], cancf[101][101][40];
void Es() {
	flag[1]= 1;
	for(int i= 2; i < 201; i++)
		if(!flag[i])
			for(int j= i + i; j < 201; j+= i) flag[j]= 1;
	for(int i= 1; i <= m; i++) {
		for(int j= i + 1; j <= m; j++) {
			if(!flag[i + j]) {
				canc[i][++canc[i][0]]= j, canc[j][++canc[j][0]]= i;
				canf[i][j]= canf[j][i]= 1;
			}
		}
		sort(canc[i] + 1, canc[i] + canc[i][0] + 1);
	}
	for(int i= 1; i <= m; i++) {
		for(int j= 1; j <= canc[i][0]; j++) {
			for(int k= 1; k <= m; k++) {
				if(canf[canc[i][j]][k]) cancf[i][k][++cancf[i][k][0]]= canc[i][j];
			}
		}
	}
	return;
}
int qp[11][11], chose[201];
int dfs(int nowx, int nowy) {
	if(nowx == n + 1) {
		for(register int i= 1; i <= n; i++) {
			for(register int j= 1; j <= n; j++) {
				printf("%d ", qp[i][j]);
			}
			printf("\n");
		}
		exit(0);
	}
	if(nowy == n + 1) return dfs(nowx + 1, 2);
	if(n == 9) {
		for(register int i= cancf[qp[nowx - 1][nowy]][qp[nowx][nowy - 1]][0], j; i ; i--) {
			if(!chose[j= cancf[qp[nowx - 1][nowy]][qp[nowx][nowy - 1]][i]]) {
				qp[nowx][nowy]= j, chose[j]= 1;
				if(dfs(nowx, nowy + 1)) return 1;
				chose[j]= 0;
			}
		}
	}
	else {
		for(register int i= 1, j; i <= cancf[qp[nowx - 1][nowy]][qp[nowx][nowy - 1]][0]; i++) {
			if(!chose[j= cancf[qp[nowx - 1][nowy]][qp[nowx][nowy - 1]][i]]) {
				qp[nowx][nowy]= j, chose[j]= 1;
				if(dfs(nowx, nowy + 1)) return 1;
				chose[j]= 0;
			}
		}
	}
	return 0;
}
int dfs2(int nowx) {
	if(nowx == n + 1) return dfs(2, 2);
	for(register int i= 1, j; i <= canc[qp[nowx - 1][1]][0]; i++) {
		if(!chose[j= canc[qp[nowx - 1][1]][i]]) {
			qp[nowx][1]= j, chose[j]= 1;
			if(dfs2(nowx + 1)) return 1;
			chose[j]= 0;
		}
	}
	return 0;
}

int dfs1(int nowy) {
	if(nowy == n + 1) return dfs2(2);
	for(register int i= 1, j; i <= canc[qp[1][nowy - 1]][0]; i++) {
		if(!chose[j= canc[qp[1][nowy - 1]][i]]) {
			qp[1][nowy]= j, chose[j]= 1;
			if(dfs1(nowy + 1)) return 1;
			chose[j]= 0;
		}
	}
	return 0;
}

signed main() {
	srand(time(0));
	scanf("%d", &n), m= n * n, Es();
	qp[1][1]= 1, chose[1]= 1;
	if(n != 1 && dfs1(2)) {
		for(register int i= 1; i <= n; i++) {
			for(register int j= 1; j <= n; j++) {
				printf("%d ", qp[i][j]);
			}
			printf("\n");
		}
	}
	else {
		printf("NO\n");
	}
	return 0;
}
