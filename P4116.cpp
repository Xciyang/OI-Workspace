#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
int n, q, tmpx, tmpy, fa[100005], dep[100005], siz[100005], hson[100005];
vector< int > edg[100005];
void dfs1(int nown) {
	siz[nown]= 1;
	for(int i= 0, to; i < (int)edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa[nown]) continue;
		dep[to]= dep[nown] + 1, fa[to]= nown;
		dfs1(to), siz[nown]+= siz[to];
		if(siz[to] > siz[hson[nown]]) hson[nown]= to;
	}
	return;
}
int id[100005], idptr, fid[100005], top[100005];
void dfs2(int nown, int tf) {
	id[nown]= ++idptr, fid[idptr]= nown, top[nown]= tf;
	if(hson[nown]) dfs2(hson[nown], tf);
	for(int i= 0, to; i < (int)edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa[nown] || to == hson[nown]) continue;
		dfs2(to, to);
	}
	return;
}
int minx[400005], flag[100005];
void update(int nown, int l, int r, int mlr, int c) {
	if(l == r) {
		minx[nown]= c ? 0x3f3f3f3f : mlr;
		return;
	}
	int mid= (l + r) >> 1;
	if(mid >= mlr) update(nown << 1, l, mid, mlr, c);
	if(mid < mlr) update(nown << 1 | 1, mid + 1, r, mlr, c);
	minx[nown]= min(minx[nown << 1], minx[nown << 1 | 1]);
	return;
}
int query(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) return minx[nown];
	int mid= (l + r) >> 1, res= 0x3f3f3f3f;
	if(mid >= ml) res= min(res, query(nown << 1, l, mid, ml, mr));
	if(mid < mr) res= min(res, query(nown << 1 | 1, mid + 1, r, ml, mr));
	return res;
}
int Query(int x, int y) {
	int res= 0x3f3f3f3f;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		res= min(res, query(1, 1, n, id[top[x]], id[x])), x= fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	res= min(res, query(1, 1, n, id[x], id[y]));
	return res == 0x3f3f3f3f ? -1 : fid[res];
}
int main() {
	cin >> n >> q;
	for(int i= 1; i < n; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(tmpy), edg[tmpy].push_back(tmpx);
	}
	dfs1(1), dfs2(1, 1);
	memset(minx, 0x3f, sizeof(minx));
	while(q--) {
		cin >> tmpx >> tmpy;
		if(!tmpx) {
			update(1, 1, n, id[tmpy], flag[tmpy]), flag[tmpy]= !flag[tmpy];
		}
		else {
			cout << Query(tmpy, 1) << endl;
		}
	}
	return 0;
}