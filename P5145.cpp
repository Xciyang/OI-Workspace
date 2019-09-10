#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
using namespace std;
int n, tox[100001], toy[100001], rex[100001], tmpx, ans, walkpast[100001], lw[100001];
void dfs(int nown) {
	memcpy(walkpast, lw, sizeof(walkpast));
	int sum= 0, to= nown;
	while(!walkpast[to]) {
		walkpast[to]= 1;
		sum+= toy[to], to= tox[to];
	}
	if(to != nown) {
		lw[nown]= 1;
		return;
	}
	memcpy(lw, walkpast, sizeof(walkpast));
	ans= max(ans, sum);
	return;
}
int main() {
	scanf("%d", &n);
	for(int i= 1; i <= n; i++) scanf("%d%d", tox + i, toy + i), rex[tox[i]]= i;
	while(clock() < CLOCKS_PER_SEC * 0.9) {
		int tmpx= rand() % n + 1;
		if(!walkpast[tmpx]) dfs(tmpx);
	}
	printf("%d\n", ans);
	return 0;
}