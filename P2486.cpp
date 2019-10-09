#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int n, m, col[100005], fa[100005], dep[100005], tmpx, tmpy, tmpz, siz[100005], hson[100005];
vector< int > edg[100005];
char tmpt;
void dfs(int nown) {
	siz[nown]= 1;
	for(int i= 0, to; i < edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa[nown]) continue;
		fa[to]= nown, dep[to]= dep[nown] + 1, dfs(to);
		siz[nown]+= siz[to];
		if(siz[to] > siz[hson[nown]]) hson[nown]= to;
	}
	return;
}
int id[100005], idptr, v[100005], top[100005];
void dfs2(int nown, int tf) {
	id[nown]= ++idptr, v[idptr]= col[nown], top[nown]= tf;
	if(hson[nown]) dfs2(hson[nown], tf);
	for(int i= 0, to; i < edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa[nown] || to == hson[nown]) continue;
		dfs2(to, to);
	}
	return;
}
int sum[400005], lc[400005], rc[400005], lazyz[400005];
void build(int nown, int l, int r) {
	if(l == r) {
		sum[nown]= 1, lc[nown]= rc[nown]= v[l];
		return;
	}
	int mid= (l + r) >> 1;
	build(nown << 1, l, mid), build(nown << 1 | 1, mid + 1, r);
	sum[nown]= sum[nown << 1] + sum[nown << 1 | 1] - (rc[nown << 1] == lc[nown << 1 | 1]);
	lc[nown]= lc[nown << 1], rc[nown]= rc[nown << 1 | 1];
	return;
}
void pushd(int nown) {
	lazyz[nown << 1]= lazyz[nown << 1 | 1]= lazyz[nown];
	sum[nown << 1]= sum[nown << 1 | 1]= 1, lc[nown << 1]= rc[nown << 1]= lc[nown << 1 | 1]= rc[nown << 1 | 1]= lazyz[nown];
	lazyz[nown]= 0;
	return;
}
void update(int nown, int l, int r, int ml, int mr, int c) {
	if(ml <= l && r <= mr) {
		lazyz[nown]= lc[nown]= rc[nown]= c, sum[nown]= 1;
		return;
	}
	if(lazyz[nown]) pushd(nown);
	int mid= (l + r) >> 1;
	if(mid >= ml) update(nown << 1, l, mid, ml, mr, c);
	if(mid < mr) update(nown << 1 | 1, mid + 1, r, ml, mr, c);
	sum[nown]= sum[nown << 1] + sum[nown << 1 | 1] - (rc[nown << 1] == lc[nown << 1 | 1]);
	lc[nown]= lc[nown << 1], rc[nown]= rc[nown << 1 | 1];
	return;
}
int Lc, Rc;
int query(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) {
		if(l == ml) Lc= lc[nown];
		if(r == mr) Rc= rc[nown];
		return sum[nown];
	}
	if(lazyz[nown]) pushd(nown);
	int mid= (l + r) >> 1, res= 0;
	if(mid >= ml) res+= query(nown << 1, l, mid, ml, mr);
	if(mid < mr) res+= query(nown << 1 | 1, mid + 1, r, ml, mr);
	if(mid >= ml && mid < mr) res-= (rc[nown << 1] == lc[nown << 1 | 1]);
	return res;
}
void Update(int x, int y, int c) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		update(1, 1, n, id[top[x]], id[x], c), x= fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	update(1, 1, n, id[x], id[y], c);
	return;
}
int Query(int x, int y) {
	int lastlc= -1, lastrc= -1, res= 0;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y), swap(lastlc, lastrc);
		res+= query(1, 1, n, id[top[x]], id[x]);
		if(lastlc == Rc) --res;
		lastlc= Lc, x= fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y), swap(lastlc, lastrc);
	res+= query(1, 1, n, id[x], id[y]);
	if(lastlc == Lc) --res;
	if(lastrc == Rc) --res;
	return res;
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) cin >> col[i];
	for(int i= 1; i < n; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(tmpy), edg[tmpy].push_back(tmpx);
	}
	dfs(1), dfs2(1, 1), build(1, 1, n);
	for(int i= 1; i <= m; i++) {
		cin >> tmpt >> tmpx >> tmpy;
		if(tmpt == 'Q')
			cout << Query(tmpx, tmpy) << endl;
		else {
			cin >> tmpz;
			Update(tmpx, tmpy, tmpz);
		}
	}
	return 0;
}
