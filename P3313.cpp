#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int n, q, tmpx, tmpy, w[100005], pc[100005];
struct NODE {
	int sumx, maxx;
	NODE *ln, *rn;
	void makeup() {
		maxx = sumx = 0;
		if(ln) {
			sumx += ln->sumx;
			maxx = max(maxx, ln->maxx);
		}
		if(rn) {
			sumx += rn->sumx;
			maxx = max(maxx, rn->maxx);
		}
		return;
	}
	void nextr() {
		if(!ln) ln = new NODE();
		if(!rn) rn = new NODE();
		return;
	}
} rt[100005];
void update(NODE *nown, int l, int r, int mlr, int c) {
	if(l == r) {
		nown->maxx = nown->sumx = c;
		return;
	}
	nown->nextr();
	int mid = (l + r) >> 1;
	if(mid >= mlr)
		update(nown->ln, l, mid, mlr, c);
	else
		update(nown->rn, mid + 1, r, mlr, c);
	nown->makeup();
	return;
}
struct RESULT {
	int x, y;
	RESULT &operator+=(const RESULT &res2) {
		x += res2.x;
		y = max(y, res2.y);
		return *this;
	}
};
RESULT query(NODE *nown, int l, int r, int ml, int mr) {
	if(!nown) return RESULT{0, 0};
	if(ml <= l && r <= mr) return RESULT{nown->sumx, nown->maxx};
	int mid = (l + r) >> 1;
	RESULT res = {0, 0};
	if(mid >= ml) res += query(nown->ln, l, mid, ml, mr);
	if(mid < mr) res += query(nown->rn, mid + 1, r, ml, mr);
	return res;
}

vector< int > edg[100005];
int dep[100005], fa[100005], siz[100005], hson[100005];
void dfs1(int nown) {
	dep[nown] = dep[fa[nown]] + 1;
	siz[nown] = 1;
	for(int i = 0, to; i < edg[nown].size(); i++) {
		to = edg[nown][i];
		if(to == fa[nown]) continue;
		fa[to] = nown, dfs1(to), siz[nown] += siz[to];
		if(siz[to] > siz[hson[nown]]) hson[nown] = to;
	}
	return;
}
int dfn[100005], topf[100005], deptr;
void dfs2(int nown, int tf) {
	dfn[nown] = ++deptr, topf[nown] = tf;
	if(hson[nown]) dfs2(hson[nown], tf);
	for(int i = 0, to; i < edg[nown].size(); i++) {
		to = edg[nown][i];
		if(to == fa[nown] || to == hson[nown]) continue;
		dfs2(to, to);
	}
	return;
}
RESULT Query(int x, int y, int k) {
	RESULT res = {0, 0};
	while(topf[x] != topf[y]) {
		if(dep[topf[x]] < dep[topf[y]]) swap(x, y);
		res += query(&rt[k], 1, n, dfn[topf[x]], dfn[x]);
		x = fa[topf[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	res += query(&rt[k], 1, n, dfn[x], dfn[y]);
	return res;
}
char tmps[3];
int main() {
	cin >> n >> q;
	for(int i = 1; i <= n; i++) {
		cin >> w[i] >> pc[i];
	}
	for(int i = 1; i < n; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(tmpy);
		edg[tmpy].push_back(tmpx);
	}
	dfs1(1), dfs2(1, 1);
	for(int i = 1; i <= n; i++) update(&rt[pc[i]], 1, n, dfn[i], w[i]);
	for(int i = 1; i <= q; i++) {
		cin >> tmps >> tmpx >> tmpy;
		if(tmps[0] == 'C') {
			if(tmps[1] == 'C') {
				update(&rt[pc[tmpx]], 1, n, dfn[tmpx], 0);
				pc[tmpx] = tmpy;
				update(&rt[pc[tmpx]], 1, n, dfn[tmpx], w[tmpx]);
			}
			else {
				w[tmpx] = tmpy;
				update(&rt[pc[tmpx]], 1, n, dfn[tmpx], w[tmpx]);
			}
		}
		else {
			auto res = Query(tmpx, tmpy, pc[tmpx]);
			if(tmps[1] == 'S') {
				cout << res.x << endl;
			}
			else {
				cout << res.y << endl;
			}
		}
	}
	return 0;
}