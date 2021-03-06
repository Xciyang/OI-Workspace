#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
int n, m, e, tmpx, tmpy, N;
vector< int > edg[605];
int pre[605], nxt[605], col[605], fa[605];
inline int getf(int x) {
	return fa[x] == x ? x : fa[x] = getf(fa[x]);
}
int flg[605], fptr;
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
	for(int i = 1; i <= N; i++) fa[i] = i, pre[i] = col[i] = 0;
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
int T;
int main() {
	cin >> T;
	while(T--) {
		cin >> n >> m >> e;
		N = n + m * 3;
		for(int i = 1; i <= N; i++) edg[i].clear(), nxt[i] = 0;
		for(int i = 1; i <= e; i++) {
			cin >> tmpx >> tmpy;
			edg[tmpx].push_back(n + m * 0 + tmpy);
			edg[tmpx].push_back(n + m * 1 + tmpy);
			edg[tmpx].push_back(n + m * 2 + tmpy);
			edg[n + m * 0 + tmpy].push_back(tmpx);
			edg[n + m * 1 + tmpy].push_back(tmpx);
			edg[n + m * 2 + tmpy].push_back(tmpx);
		}
		for(int i = 1; i <= m; i++) {
			edg[n + m * 0 + i].push_back(n + m * 1 + i);
			edg[n + m * 0 + i].push_back(n + m * 2 + i);
			edg[n + m * 1 + i].push_back(n + m * 0 + i);
			edg[n + m * 1 + i].push_back(n + m * 2 + i);
			edg[n + m * 2 + i].push_back(n + m * 0 + i);
			edg[n + m * 2 + i].push_back(n + m * 1 + i);
		}
		int res = -n;
		for(int i = 1; i <= N; i++)
			if(!nxt[i]) res += BFS(i);
		cout << res << endl;
		for(int i = 1; i <= n; i++) cout << ((nxt[i] - n) % m ? (nxt[i] - n) % m : m) << ' ';
		cout << endl;
	}
	return 0;
}