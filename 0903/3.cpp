#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m, dy[50][30], tmpl, tmpx, nowc[30], bestans;
char tmps[101];
long long ct[50];
void dfs(int nown, long long cs, int can) {
	if(nown == m + 1) {
		bestans= max(bestans, can);
		return;
	}
	dfs(nown + 1, cs, can);
	if(!(ct[nown] & cs)) dfs(nown + 1, cs | (1ll << nown), can + 1);
	return;
}
void init() {
	for(int i= 1, k; i <= m; i++) {
		for(int j= i + 1; j <= m; j++) {
			for(k= 0; k < n; k++)
				if(dy[i][k] && dy[j][k] && dy[i][k] != dy[j][k]) break;
			if(k != n) ct[i]|= (1ll << j), ct[j]|= (1ll << i);
		}
	}
	return;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i= 1; i <= m; i++) {
		scanf("%s", tmps), tmpl= strlen(tmps);
		for(int j= 0; j < tmpl; j++) scanf("%d", &dy[i][tmps[j] - 'A']);
	}
	init(), dfs(1, 0, 0);
	printf("%d\n", bestans);
	return 0;
}