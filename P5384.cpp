#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, q, fa[1000001][20], head[1000001], edptr= 1, tmpx, tmpk, ans[1000001], maxdep;
struct edge {
	int to, nexty;
} eds[1000001];
void add(int a, int b) {
	eds[edptr].to= b, eds[edptr].nexty= head[a];
	head[a]= edptr++;
	return;
}
int dep[1000001], dfn[1000001], dfptr, siz[1000001];
void dfs(int nown) {
	dep[nown]= dep[fa[nown][0]] + 1, dfn[nown]= ++dfptr, siz[nown]= 1, maxdep= max(maxdep, dep[nown]);
	for(int i= head[nown]; i; i= eds[i].nexty) dfs(eds[i].to), siz[nown]+= siz[eds[i].to];
	return;
}
int head2[1000001], rptr= 1;
struct req {
	int l, r, id, nexty;
} reqs[1000001];
inline int getfa(int nown, int k) {
	for(int i= 0; i < 20; i++)
		if((k >> i) & 1) nown= fa[nown][i];
	return nown;
}
int bitsarr[1000001];
#define lowb(i) ((i) & -(i))
inline int queryb(int i) {
	int ans= 0;
	for(; i; i-= lowb(i)) ans+= bitsarr[i];
	return ans;
}
inline int read() {
	int e= 0;
	char ch= getchar();
	while(ch < '0' || ch > '9') ch= getchar();
	while(ch >= '0' && ch <= '9') e= e * 10 + ch - '0', ch= getchar();
	return e;
}
inline int put(int i) {
	if(i > 9) put(i / 10);
	return putchar('0' + i % 10);
}
int main() {
	n= read(), q= read();
	for(register int i= 2; i <= n; i++) fa[i][0]= read(), add(fa[i][0], i);
	dfs(1);
	for(int i= 1; i < 20; i++)
		for(register int j= 1; j <= n; j++) fa[j][i]= fa[fa[j][i - 1]][i - 1];
	memset(head, 0, sizeof(head)), edptr= 1;
	for(register int i= 1; i <= n; i++) add(dep[i], dfn[i]);
	for(int i= 1; i <= q; i++) {
		tmpx= read(), tmpk= read();
		if(tmpk >= dep[tmpx]) continue;
		tmpx= getfa(tmpx, tmpk), tmpk= dep[tmpx] + tmpk;
		reqs[rptr]= req{dfn[tmpx], dfn[tmpx] + siz[tmpx] - 1, i, head2[tmpk]};
		head2[tmpk]= rptr++;
	}
	for(int i= 1; i <= maxdep; i++) {
		for(int j= head[i]; j; j= eds[j].nexty)
			for(register int k= eds[j].to; k <= n; k+= lowb(k)) ++bitsarr[k];
		for(int j= head2[i]; j; j= reqs[j].nexty) ans[reqs[j].id]= queryb(reqs[j].r) - queryb(reqs[j].l - 1) - 1;
		for(int j= head[i]; j; j= eds[j].nexty)
			for(register int k= eds[j].to; k <= n; k+= lowb(k)) --bitsarr[k];
	}
	for(register int i= 1; i <= q; i++) put(ans[i]), putchar(' ');
	putchar('\n');
	return 0;
}