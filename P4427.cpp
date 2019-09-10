#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int n, m, head[300005], edptr= 1, pows[51], tmpx, tmpy, tmpz;
struct EDGE {
	int to, nexty;
} eds[600005];
void add(int a, int b) {
	eds[edptr].to= b, eds[edptr].nexty= head[a];
	head[a]= edptr++;
	return;
}
int f[300005][21], dep[300005], val[300005][51];
void dfs(int nown) {
	for(int i= 0; f[nown][i]; i++) f[nown][i + 1]= f[f[nown][i]][i];
	for(int i= 1; i <= 50; i++) pows[i]= ((long long)pows[i - 1] * dep[nown]) % 998244353, val[nown][i]= ((long long)val[f[nown][0]][i] + pows[i]) % 998244353;
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == f[nown][0]) continue;
		val[to][0]= val[nown][0] + 1, dep[to]= dep[nown] + 1, f[to][0]= nown, dfs(to);
	}
	return;
}
int lca(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i= 20; i >= 0; i--) {
		if(dep[f[x][i]] >= dep[y]) x= f[x][i];
		if(x == y) return x;
	}
	for(int i= 20; i >= 0; i--)
		if(f[x][i] != f[y][i]) x= f[x][i], y= f[y][i];
	return f[x][0];
}
int main() {
    scanf("%d", &n);
	for(int i= 1; i < n; i++) {
         scanf("%d%d", &tmpx, &tmpy);
		add(tmpx, tmpy), add(tmpy, tmpx);
	}
	pows[0]= 1, dfs(1);
	    scanf("%d", &m);
	for(int i= 1; i <= m; i++) {
		scanf("%d%d%d", &tmpx, &tmpy, &tmpz);
        printf("%d\n", (((long long)val[tmpx][tmpz] + val[tmpy][tmpz] - val[lca(tmpx, tmpy)][tmpz] - val[f[lca(tmpx, tmpy)][0]][tmpz]) % 998244353 + 998244353) % 998244353);
	}
	return 0;
}