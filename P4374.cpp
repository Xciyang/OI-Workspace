#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
int n, m, tmpx, tmpy, tmpz, fa[50005], dep[50005], siz[50005], hson[50005];
vector< int > edg[50005];
int ff[50005], tt[50005];
void dfs1(int nown) {
	siz[nown]= 1;
	for(int i= 0, to; i < edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa[nown]) continue;
		fa[to]= nown, dep[to]= dep[nown] + 1;
		dfs1(to), siz[nown]+= siz[to];
		if(siz[to] > siz[hson[nown]]) hson[nown]= to;
	}
	return;
}
int id[50005], idptr, top[50005];
void dfs2(int nown, int tf) {
	id[nown]= ++idptr, top[nown]= tf;
	if(hson[nown]) dfs2(hson[nown], tf);
	for(int i= 0, to; i < edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == hson[nown] || to == fa[nown]) continue;
		dfs2(to, to);
	}
	return;
}
int minx[300005], laz[300005];
void pd(int nown) {
	laz[nown << 1]= min(laz[nown << 1], laz[nown]);
	laz[nown << 1 | 1]= min(laz[nown << 1 | 1], laz[nown]);
	minx[nown << 1]= min(minx[nown << 1], laz[nown]);
	minx[nown << 1 | 1]= min(minx[nown << 1 | 1], laz[nown]);
	laz[nown]= 0x3f3f3f3f;
	return;
}
void update(int nown, int l, int r, int ml, int mr, int c) {
	if(ml <= l && r <= mr) {
		minx[nown]= min(minx[nown], c), laz[nown]= min(laz[nown], c);
		return;
	}
	if(laz[nown] != 0x3f3f3f3f) pd(nown);
	int mid= (l + r) >> 1;
	if(mid >= ml) update(nown << 1, l, mid, ml, mr, c);
	if(mid < mr) update(nown << 1 | 1, mid + 1, r, ml, mr, c);
	minx[nown]= min(minx[nown << 1], minx[nown << 1 | 1]);
	return;
}
int query(int nown, int l, int r, int mlr) {
	if(l == r) return minx[nown];
	if(laz[nown] != 0x3f3f3f3f) pd(nown);
	int mid= (l + r) >> 1;
	if(mid >= mlr) return query(nown << 1, l, mid, mlr);
	return query(nown << 1 | 1, mid + 1, r, mlr);
}
void Update(int x, int y, int c) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		update(1, 1, n, id[top[x]], id[x], c);
		x= fa[top[x]];
	}
	if(x != y) {
		if(id[x] > id[y]) swap(x, y);
		update(1, 1, n, id[x] + 1, id[y], c);
	}
	return;
}
int main() {
	cin >> n >> m;
	for(int i= 1; i < n; i++) cin >> ff[i] >> tt[i], edg[ff[i]].push_back(tt[i]), edg[tt[i]].push_back(ff[i]);
	dfs1(1), dfs2(1, 1), memset(minx, 0x3f, sizeof(minx)), memset(laz, 0x3f, sizeof(laz));
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		Update(tmpx, tmpy, tmpz);
	}
	for(int i= 1; i < n; i++) {
		tmpx= query(1, 1, n, id[dep[ff[i]] > dep[tt[i]] ? ff[i] : tt[i]]);
		cout << (tmpx == 0x3f3f3f3f ? -1 : tmpx) << endl;
	}
	return 0;
}