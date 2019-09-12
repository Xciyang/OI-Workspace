#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <string.h>
using namespace std;
int n, m, tmpx, tmpy, tmpz, cnt;
map< int, map< int, int > > mm;
vector< int > edg[30005], edg2[30005];
struct OP {
	int opt, x, y, ans;
} ops[40005];
int wp[30005], fa[30005], siz[30005], hson[30005], dep[30005];
void dfs1(int nown) {
	siz[nown]= wp[nown]= 1;
	for(int i= 0, to; i < (int)edg[nown].size(); i++) {
		to= edg[nown][i];
		if(wp[to] || mm[nown][to]) continue;
		mm[nown][to]= mm[to][nown]= 1, fa[to]= nown, dep[to]= dep[nown] + 1, edg2[nown].push_back(to);
		dfs1(to), siz[nown]+= siz[to];
		if(siz[to] > siz[hson[nown]]) hson[nown]= to;
	}
	return;
}
int id[30005], idptr, top[30005];
void dfs2(int nown, int tf) {
	id[nown]= ++idptr, top[nown]= tf;
	if(hson[nown]) dfs2(hson[nown], tf);
	for(int i= 0, to; i < edg2[nown].size(); i++) {
		to= edg2[nown][i];
		if(to == hson[nown]) continue;
		dfs2(to, to);
	}
	return;
}
int v[200005], lazy[200005];
void build(int nown, int l, int r) {
	lazy[nown]= 1;
	if(l == r) {
		v[nown]= 1;
		return;
	}
	int mid= (l + r) >> 1;
	build(nown << 1, l, mid), build(nown << 1 | 1, mid + 1, r);
	v[nown]= v[nown << 1] + v[nown << 1 | 1];
	return;
}
void pd(int nown) {
	v[nown << 1]= v[nown << 1 | 1]= lazy[nown << 1]= lazy[nown << 1 | 1]= 0;
	lazy[nown]= 1;
	return;
}
void update(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) {
		v[nown]= 0, lazy[nown]= 0;
		return;
	}
	int mid= (l + r) >> 1;
	if(!lazy[nown]) pd(nown);
	if(mid >= ml) update(nown << 1, l, mid, ml, mr);
	if(mid < mr) update(nown << 1 | 1, mid + 1, r, ml, mr);
	v[nown]= v[nown << 1] + v[nown << 1 | 1];
	return;
}
int query(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) return v[nown];
	int mid= (l + r) >> 1, res= 0;
	if(!lazy[nown]) pd(nown);
	if(mid >= ml) res+= query(nown << 1, l, mid, ml, mr);
	if(mid < mr) res+= query(nown << 1 | 1, mid + 1, r, ml, mr);
	return res;
}
void Update(int x, int y) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		update(1, 1, n, id[top[x]], id[x]);
		x= fa[top[x]];
	}
	if(x != y) {
		if(dep[x] > dep[y]) swap(x, y);
		update(1, 1, n, id[x] + 1, id[y]);
	}
	return;
}
int Query(int x, int y) {
	int res= 0;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		res+= query(1, 1, n, id[top[x]], id[x]);
		x= fa[top[x]];
	}
	if(x != y) {
		if(dep[x] > dep[y]) swap(x, y);
		res+= query(1, 1, n, id[x] + 1, id[y]);
	}
	return res;
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(tmpy), edg[tmpy].push_back(tmpx);
	}
	while(true) {
		cin >> tmpx;
		if(tmpx == -1) break;
		cin >> tmpy >> tmpz;
		ops[++cnt]= OP{tmpx, tmpy, tmpz, 0};
		if(!tmpx) mm[tmpy][tmpz]= mm[tmpz][tmpy]= 1;
	}
	dfs1(1), dfs2(1, 1), build(1, 1, n);
	for(int i= 1, to; i <= n; i++) {
		for(int j= 0; j < edg[i].size(); j++) {
			to= edg[i][j];
			if(mm[i][to]) continue;
			Update(i, to);
		}
	}
	for(int i= cnt; i; i--) {
		if(ops[i].opt) {
			ops[i].ans= Query(ops[i].x, ops[i].y);
		}
		else {
			Update(ops[i].x, ops[i].y);
		}
	}
	for(int i= 1; i <= cnt; i++) {
		if(ops[i].opt) cout << ops[i].ans << endl;
	}
	return 0;
}