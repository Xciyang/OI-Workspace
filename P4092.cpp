#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int n, q, tmpx, tmpy, dep[100005], fa[100005], hson[100005], siz[100005];
vector< int > edg[100005];
void dfs1(int nown) {
	siz[nown]= 1;
	for(int i= 0, to; i < edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa[nown]) continue;
		fa[to]= nown, dep[to]= dep[nown] + 1;
		dfs1(to), siz[nown]+= siz[to];
		if(siz[hson[nown]] < siz[to]) hson[nown]= to;
	}
	return;
}
int idd[100005], idptr, fid[100005], top[100005];
void dfs2(int nown, int tf) {
	idd[nown]= ++idptr, fid[idptr]= nown, top[nown]= tf;
	if(hson[nown]) dfs2(hson[nown], tf);
	for(int i= 0, to; i < edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa[nown] || to == hson[nown]) continue;
		dfs2(to, to);
	}
	return;
}
int maxx[400005];
char oper;
void update(int nown, int l, int r, int c) {
	if(l == r) {
		maxx[nown]= c;
		return;
	}
	int mid= (l + r) >> 1;
	if(mid >= c)
		update(nown << 1, l, mid, c);
	else
		update(nown << 1 | 1, mid + 1, r, c);
	maxx[nown]= max(maxx[nown << 1], maxx[nown << 1 | 1]);
	return;
}
int query(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) return maxx[nown];
	int mid= (l + r) >> 1, res= 1;
	if(mid >= ml) res= max(res, query(nown << 1, l, mid, ml, mr));
	if(mid < mr) res= max(res, query(nown << 1 | 1, mid + 1, r, ml, mr));
	return res;
}
int Query(int x, int y) {
	int res= 1;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		res= max(res, fid[query(1, 1, n, idd[top[x]], idd[x])]);
		x= fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	res= max(res, fid[query(1, 1, n, idd[x], idd[y])]);
	return res;
}
int main() {
	scanf("%d%d", &n, &q);
	for(int i= 1; i < n; i++) {
		scanf("%d%d", &tmpx, &tmpy);
		edg[tmpx].push_back(tmpy), edg[tmpy].push_back(tmpx);
	}
	dfs1(1), dfs2(1, 1);
	while(q--) {
		scanf(" %c%d", &oper, &tmpx);
		if(oper == 'Q') {
			printf("%d\n", Query(tmpx, 1));
		}
		else {
			update(1, 1, n, idd[tmpx]);
		}
	}
	return 0;
}