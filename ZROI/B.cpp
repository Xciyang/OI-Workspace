#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
int n, m, tmpx, tmpy, v[400005], fa[100005], siz[100005], hson[100005], dep[100005];
struct EDG {
	int to, dis;
	EDG(int to0) : to(to0) {}
};
vector< EDG > edg[100005];
long long ans;
void dfs(int nown) {
	siz[nown]= 1;
	for(int i= 0, to; i < (int)edg[nown].size(); i++) {
		to= edg[nown][i].to;
		if(to == fa[nown]) continue;
		fa[to]= nown, dep[to]= dep[nown] + 1, dfs(to), siz[nown]+= siz[to];
		if(siz[to] > siz[hson[nown]]) hson[nown]= to;
	}
	return;
}
int idd[100005], idptr, top[100005];
void dfs2(int nown, int tf) {
	idd[nown]= ++idptr, top[nown]= tf;
	if(hson[nown]) dfs2(hson[nown], tf);
	for(int i= 0, to; i < edg[nown].size(); i++) {
		to= edg[nown][i].to;
		if(to == fa[nown] || to == hson[nown]) continue;
		dfs2(to, to);
	}
	return;
}
int lazyz[400005];
void pd(int nown) {
	v[nown << 1]+= lazyz[nown], v[nown << 1 | 1]+= lazyz[nown];
	lazyz[nown << 1]+= lazyz[nown], lazyz[nown << 1 | 1]+= lazyz[nown];
	lazyz[nown]= 0;
	return;
}
void update(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) {
		++v[nown], ++lazyz[nown];
		return;
	}
	if(lazyz[nown]) pd(nown);
	int mid= (l + r) >> 1;
	if(mid >= ml) update(nown << 1, l, mid, ml, mr);
	if(mid < mr) update(nown << 1 | 1, mid + 1, r, ml, mr);
	v[nown]= v[nown << 1] + v[nown << 1 | 1];
	return;
}
int query(int nown, int l, int r, int mlr) {
	if(l == r) return v[nown];
	if(lazyz[nown]) pd(nown);
	int mid= (l + r) >> 1;
	if(mid >= mlr) return query(nown << 1, l, mid, mlr);
	return query(nown << 1 | 1, mid + 1, r, mlr);
}
void Update(int x, int y) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		update(1, 1, n, idd[top[x]], idd[x]), x= fa[top[x]];
	}
	if(x != y) {
		if(dep[x] > dep[y]) swap(x, y);
		update(1, 1, n, idd[x] + 1, idd[y]);
	}
	return;
}
int edptr, r[100005];
struct EDGE {
	int x, y, dis;
	EDGE() {}
	EDGE(int x0, int y0, int dis0) {
		x= x0, y= y0, dis= dis0;
	}
	inline int operator<(const EDGE &e2) const {
		return dis > e2.dis;
	}
} edg2[100005];
void dfs3(int nown) {
	for(int i= 0, to; i < (int)edg[nown].size(); i++) {
		to= edg[nown][i].to;
		if(to == fa[nown]) continue;
		edg2[++edptr]= EDGE(nown, to, query(1, 1, n, idd[to]));
		dfs3(to);
	}
	return;
}
int f[100005][2];
void dfs4(int nown) {
	int lest= 0, sum= 0;
	for(int i= 0, to; i < (int)edg[nown].size(); i++) {
		to= edg[nown][i].to;
		if(to == fa[nown]) continue;
		edg[nown][i].dis= query(1, 1, n, idd[to]);
	}
	return;
}
int main() {
	// freopen("ex_hld3.in", "r", stdin);
	cin >> n >> m;
	for(int i= 1; i < n; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(EDG(tmpy)), edg[tmpy].push_back(EDG(tmpx));
	}
	dfs(1), dfs2(1, 1);
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy;
		Update(tmpx, tmpy);
	}
	dfs3(1);
	sort(edg2 + 1, edg2 + edptr + 1);
	int k= 0;
	for(int i= 1; i <= edptr; i++) {
		if(r[edg2[i].x] >= 2 || r[edg2[i].y] >= 2) {
			ans+= edg2[i].dis;
			continue;
		}
		++r[edg2[i].x], ++r[edg2[i].y];
	}
	cout << ans << endl;
	return 0;
}
/*
4 3
1 2
2 3
2 4
1 3
1 4
3 4
*/

/*
6 5
1 2
1 3
2 4
3 5
1 6
4 5
4 3
4 1
4 2
1 6

1
*/