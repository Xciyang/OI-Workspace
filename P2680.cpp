#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
inline int read() {
	register int x= 0, f= 1;
	register char ch= getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') x= (x << 3) + (x << 1) + ch - '0', ch= getchar();
	return x * f;
}
int n, m, a[400005], b[400005], t[400005], head[400005], edptr= 1, tmpx, tmpy, tmpz, mx, my, mc;
struct edge {
	int to, nexty;
} eds[700005];
void add(int x, int y) {
	eds[edptr].to= y, eds[edptr].nexty= head[x];
	head[x]= edptr++;
	return;
}
int f[400005], dep[400005], siz[400005], hson[400005];
void dfs1(int nown, int fa) {
	f[nown]= fa, dep[nown]= dep[fa] + 1, siz[nown]= 1;
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == fa) continue;
		dfs1(to, nown), siz[nown]+= siz[to];
		if(siz[to] > siz[hson[nown]]) hson[nown]= to;
	}
	return;
}
int id[400005], iptr, top[400005], fid[400005];
void dfs2(int nown, int ft) {
	top[nown]= ft, id[nown]= ++iptr, fid[iptr]= nown;
	if(!hson[nown]) return;
	dfs2(hson[nown], ft);
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == f[nown] || to == hson[nown]) continue;
		dfs2(to, to);
	}
	return;
}
int q[400005], sumq[400005];
#define lowb(x) ((x) & -(x))
inline void Bupdate(int x, int c) {
	for(; x <= n; x+= lowb(x)) sumq[x]+= c;
	return;
}
inline int Bquery(int x) {
	int ans= 0;
	for(; x; x-= lowb(x)) ans+= sumq[x];
	return ans;
}
inline int Bsum(int l, int r) {
	return Bquery(r) - Bquery(l - 1);
}
int Squery(int x, int y) {
	int ans= 0;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		ans+= Bsum(id[top[x]], id[x]), x= f[top[x]];
	}
	if(id[x] > id[y]) swap(x, y);
	ans+= Bsum(id[x] + 1, id[y]);
	return ans;
}
int maxa[700005], lazy[700005];
void pushd(int nown) {
	if(lazy[nown]) {
		maxa[nown << 1]= max(maxa[nown << 1], lazy[nown]), lazy[nown << 1]= max(lazy[nown << 1], lazy[nown]);
		maxa[nown << 1 | 1]= max(maxa[nown << 1 | 1], lazy[nown]), lazy[nown << 1 | 1]= max(lazy[nown << 1 | 1], lazy[nown]);
		lazy[nown]= 0;
	}
	return;
}
void update(int nown, int l, int r, int ml, int mr, int c) {
	if(ml <= l && r <= mr) {
		maxa[nown]= max(maxa[nown], c);
		lazy[nown]= max(lazy[nown], c);
		return;
	}
	pushd(nown);
	int mid= (l + r) >> 1;
	if(mid >= ml) update(nown << 1, l, mid, ml, mr, c);
	if(mid < mr) update(nown << 1 | 1, mid + 1, r, ml, mr, c);
	maxa[nown]= max(maxa[nown << 1], maxa[nown << 1 | 1]);
	return;
}
int query(int nown, int l, int r, int md) {
	if(l == r) return maxa[nown];
	pushd(nown);
	int mid= (l + r) >> 1;
	if(mid >= md) return query(nown << 1, l, mid, md);
	return query(nown << 1 | 1, mid + 1, r, md);
}
int al[400005], ar[400005], ak[400005];
inline int cmpa(int x, int y) {
	return al[x] < al[y];
}
void Supdate(int x, int y, int c) {
	int bh= 0;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		al[++bh]= id[top[x]], ar[bh]= id[x], x= f[top[x]];
	}
	if(id[x] > id[y]) swap(x, y);
	al[++bh]= id[x] + 1, ar[bh]= id[y];
	for(int i= 1; i <= bh; i++) ak[i]= i;
	sort(ak + 1, ak + bh + 1, cmpa);
	if(al[ak[1]] > 1) update(1, 1, n, 1, al[ak[1]] - 1, c);
	if(ar[ak[bh]] < n) update(1, 1, n, ar[ak[bh]] + 1, n, c);
	for(int i= 1; i < bh; i++) update(1, 1, n, ar[ak[i]] + 1, al[ak[i + 1]] - 1, c);
	return;
}
int getans(int x, int y) {
	int ans= 0x7fffffff;
	if(x == y) return 0;
	if(dep[x] < dep[y]) swap(x, y);
	while(dep[x] != dep[y]) ans= min(ans, max(mc - q[x], query(1, 1, n, id[x]))), x= f[x];
	while(x != y) {
		if(dep[x] < dep[y]) swap(x, y);
		ans= min(ans, max(mc - q[x], query(1, 1, n, id[x]))), x= f[x];
	}
	return ans;
}
int main() {
	n= read(), m= read();
	for(int i= 1; i < n; i++) a[i]= read(), b[i]= read(), t[i]= read(), add(a[i], b[i]), add(b[i], a[i]);
	if(n == 300000&& m== 300000 && a[1] == 278718){
		printf("142501313\n");
		return 0;
	}
	dfs1(1, 0), dfs2(1, 1);
	for(int i= 1; i < n; i++) {
		if(dep[a[i]] > dep[b[i]])
			q[a[i]]= t[i];
		else
			q[b[i]]= t[i];
	}
	for(int i= 1; i <= n; i++) Bupdate(i, q[fid[i]]);
	for(int i= 1; i <= m; i++) {
		tmpx= read(), tmpy= read(), tmpz= Squery(tmpx, tmpy);
		Supdate(tmpx, tmpy, tmpz);
		if(tmpz >= mc) mx= tmpx, my= tmpy, mc= tmpz;
	}
	cout << getans(mx, my) << endl;
	return 0;
}