#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
int n, m, tmpx, tmpy, tmpz, v[100005], nroot, fa[100005][20], tmpt;
vector< int > edg[100005];
int dep[100005], hson[100005], siz[100005];
void dfs1(int nown) {
	dep[nown]= dep[fa[nown][0]] + 1, siz[nown]= 1;
	for(int i= 1; i < 20; i++) fa[nown][i]= fa[fa[nown][i - 1]][i - 1];
	for(int i= 0, to; i < (int)edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa[nown][0]) continue;
		fa[to][0]= nown, dfs1(to);
		siz[nown]+= siz[to];
		if(siz[to] > siz[hson[nown]]) hson[nown]= to;
	}
	return;
}
int idd[100005], idptr, v2[100005], topf[100005];
void dfs2(int nown, int ff) {
	idd[nown]= ++idptr, v2[idptr]= v[nown], topf[nown]= ff;
	if(hson[nown]) dfs2(hson[nown], ff);
	for(int i= 0, to; i < (int)edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa[nown][0] || to == hson[nown]) continue;
		dfs2(to, to);
	}
	return;
}
int minx[500005], lazyz[500005];
void build(int nown, int l, int r) {
	if(l == r) {
		minx[nown]= v2[l];
		return;
	}
	int mid= (l + r) >> 1;
	build(nown << 1, l, mid), build(nown << 1 | 1, mid + 1, r);
	minx[nown]= min(minx[nown << 1], minx[nown << 1 | 1]);
	return;
}
void pd(int nown) {
	lazyz[nown << 1]= lazyz[nown << 1 | 1]= minx[nown << 1]= minx[nown << 1 | 1]= lazyz[nown];
	lazyz[nown]= 0;
	return;
}
void update(int nown, int l, int r, int ml, int mr, long long c) {
	if(ml <= l && r <= mr) {
		lazyz[nown]= minx[nown]= c;
		return;
	}
	if(lazyz[nown]) pd(nown);
	int mid= (l + r) >> 1;
	if(mid >= ml) update(nown << 1, l, mid, ml, mr, c);
	if(mid < mr) update(nown << 1 | 1, mid + 1, r, ml, mr, c);
	minx[nown]= min(minx[nown << 1], minx[nown << 1 | 1]);
	return;
}
inline int query(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) return minx[nown];
	if(lazyz[nown]) pd(nown);
	int mid= (l + r) >> 1, res= 2147483647;
	if(mid >= ml) res= min(res, query(nown << 1, l, mid, ml, mr));
	if(mid < mr) res= min(res, query(nown << 1 | 1, mid + 1, r, ml, mr));
	return res;
}
inline int qufa(int x, int k) {
	for(int i= 19; i >= 0; i--)
		if(k >= (1 << i)) x= fa[x][i], k-= (1 << i);
	return x;
}
inline void updis(int x, int y, int c) {
	while(topf[x] != topf[y]) {
		if(dep[topf[x]] < dep[topf[y]]) swap(x, y);
		update(1, 1, n, idd[topf[x]], idd[x], c), x= fa[topf[x]][0];
	}
	if(dep[x] < dep[y]) swap(x, y);
	update(1, 1, n, idd[y], idd[x], c);
	return;
}
int main() { 
	scanf("%d%d", &n, &m);
	for(int i= 1; i < n; i++) {
		scanf("%d%d", &tmpx, &tmpy);
		edg[tmpx].push_back(tmpy), edg[tmpy].push_back(tmpx);
	}
	for(int i= 1; i <= n; i++) scanf("%d", v + i);
	dfs1(1), dfs2(1, 1), build(1, 1, n);
	scanf("%d", &nroot);
	while(m--) {
		scanf("%d%d", &tmpt, &tmpx);
		if(tmpt == 1)
			nroot= tmpx;
		else if(tmpt == 2) {
			scanf("%d%d", &tmpy, &tmpz);
			updis(tmpx, tmpy, tmpz);
		}
		else {
			if(nroot == tmpx)
				printf("%d\n", minx[1]);
			else if(dep[tmpx] >= dep[nroot] || (dep[tmpx] < dep[nroot] && qufa(nroot, dep[nroot] - dep[tmpx]) != tmpx))
				printf("%d\n", query(1, 1, n, idd[tmpx], idd[tmpx] + siz[tmpx] - 1));
			else {
				tmpy= qufa(nroot, dep[nroot] - dep[tmpx] - 1), tmpz= query(1, 1, n, 1, idd[tmpy] - 1);
				if(idd[tmpy] + siz[tmpy] <= n) tmpz= min(tmpz, query(1, 1, n, idd[tmpy] + siz[tmpy], n));
				printf("%d\n", tmpz);
			}
		}
	}
	return 0;
}