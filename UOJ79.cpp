#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
int n, m, tmpx, tmpy;
vector< int > edg[505];
int pre[505], nxt[505], col[505];
int fa[505];
inline int getf(int x) {
	return fa[x] == x ? x : fa[x] = getf(fa[x]);
}
int flg[505], fptr;
inline int getlca(int x, int y) {
	++fptr, x = getf(x), y = getf(y);
	while(flg[x] != fptr) {
		flg[x] = fptr;
		x = getf(pre[nxt[x]]);
		if(y) swap(x, y);
	}
	return x;
}
inline void blossom(int x, int y, int l, queue< int > &qu) {
	while(getf(x) != l) {
		pre[x] = y, y = nxt[x];
		if(col[y] == 2) col[y] = 1, qu.push(y);
		if(getf(x) == x) fa[x] = l;
		if(getf(y) == y) fa[y] = l;
		x = pre[y];
	}
	return;
}
int BFS(int nown) {
	for(int i = 1; i <= n; i++) fa[i] = i, pre[i] = col[i] = 0;
	queue< int > qu;
	qu.push(nown);
	col[nown] = 1;
	register int to;
	while(!qu.empty()) {
		nown = qu.front(), qu.pop();
		for(int i = 0; i < edg[nown].size(); i++) {
			to = edg[nown][i];
			if(getf(to) == getf(nown) || col[to] == 2) continue;
			if(!col[to]) {
				col[to] = 2, pre[to] = nown;
				if(!nxt[to]) {
					for(int j = to, lj; j; j = lj) lj = nxt[pre[j]], nxt[pre[j]] = j, nxt[j] = pre[j];
					return 1;
				}
				qu.push(nxt[to]), col[nxt[to]] = 1;
			}
			else {
				int l = getlca(nown, to);
				blossom(nown, to, l, qu);
				blossom(to, nown, l, qu);
			}
		}
	}
	return 0;
}
int main() {
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(tmpy);
		edg[tmpy].push_back(tmpx);
	}
	int res = 0;
	for(int i = 1; i <= n; i++)
		if(!nxt[i]) res += BFS(i);
	cout << res << endl;
	for(int i = 1; i <= n; i++) cout << nxt[i] << ' ';
	cout << endl;
	return 0;
}
/*
8 8
1 2
2 3
3 4
4 5
5 6
6 7
6 8
8 1
*/