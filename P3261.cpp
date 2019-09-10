#include <iostream>
#include <stdio.h>
using namespace std;
#define int long long
int n, m, head[300005], edptr= 1, h[300005], opt[300005], val[300005], tmpx;
int s[300005], rt[300005], b[300005];
struct EDGE {
	int to, nexty;
} eds[300005];
void add(int a, int b) {
	eds[edptr].to= b, eds[edptr].nexty= head[a];
	head[a]= edptr++;
	return;
}
int r[300005], l[300005], d[300005], lazyc[300005], lazya[300005];
inline void update(int x, int c1, int c2) {
	if(!x) return;
	s[x]*= c1, s[x]+= c2, lazyc[x]*= c1, lazya[x]= lazya[x] * c1 + c2;
	return;
}
inline void pushd(int x) {
	update(l[x], lazyc[x], lazya[x]), update(r[x], lazyc[x], lazya[x]);
	lazyc[x]= 1, lazya[x]= 0;
	return;
}
int merge(int x, int y) {
	if(!x || !y) return x + y;
	pushd(x), pushd(y);
	if(s[x] > s[y]) swap(x, y);
	r[x]= merge(r[x], y);
	if(d[l[x]] < d[r[x]]) swap(l[x], r[x]);
	d[x]= d[r[x]] + 1;
	return x;
}
int dep[300005], ans1[300005], ans2[300005];
void dfs(int nown) {
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to, dep[to]= dep[nown] + 1;
		dfs(to), rt[nown]= merge(rt[nown], rt[to]);
	}
	while(rt[nown] && s[rt[nown]] < h[nown]) {
		pushd(rt[nown]);
		++ans1[nown], ans2[rt[nown]]= dep[b[rt[nown]]] - dep[nown];
		rt[nown]= merge(l[rt[nown]], r[rt[nown]]);
	}
	opt[nown] ? update(rt[nown], val[nown], 0) : update(rt[nown], 1, val[nown]);
	return;
}
signed main() {
	scanf("%lld%lld", &n, &m);
	for(int i= 1; i <= n; i++) scanf("%lld", h + i);
	for(int i= 2; i <= n; i++) {
		scanf("%lld%lld%lld", &tmpx, opt + i, val + i);
		add(tmpx, i);
	}
	for(int i= 1; i <= m; i++) {
		scanf("%lld%lld", s + i, b + i);
		lazyc[i]= 1, rt[b[i]]= merge(rt[b[i]], i);
	}
	dfs(1);
	while(rt[1]) pushd(rt[1]), ans2[rt[1]]= dep[b[rt[1]]] + 1, rt[1]= merge(l[rt[1]], r[rt[1]]);
	for(int i= 1; i <= n; i++) printf("%lld\n", ans1[i]);
	for(int i= 1; i <= m; i++) printf("%lld\n", ans2[i]);
	return 0;
}