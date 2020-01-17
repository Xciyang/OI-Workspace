#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int n, k, tmpx, tmpy, tmpz;
struct EDGE {
	int to, dis;
};
vector< EDGE > edg[200005];
int siz[200005], buk[1000006], msiz[200005], rt, vis[200005], ans = 1e9;
void getRt(int nown, int fa) {
	siz[nown] = 1, msiz[nown] = 0;
	for(int i = 0, to; i < edg[nown].size(); i++) {
		to = edg[nown][i].to;
		if(to == fa || vis[to]) continue;
		getRt(to, nown), siz[nown] += siz[to], msiz[nown] = max(msiz[nown], siz[to]);
	}
	msiz[nown] = max(msiz[nown], siz[0] - siz[nown]);
	if(msiz[nown] < msiz[rt]) rt = nown;
	return;
}
void clear(int nown, int fa, int dis) {
	if(dis >= k) return;
	buk[dis] = 1e9;
	for(int i = 0, to; i < edg[nown].size(); i++) {
		to = edg[nown][i].to;
		if(to == fa || vis[to]) continue;
		clear(to, nown, dis + edg[nown][i].dis);
	}
}
void query(int nown, int fa, int dis, int w) {
	if(dis > k) return;
	ans = min(ans, buk[k - dis] + w);
	for(int i = 0, to; i < edg[nown].size(); i++) {
		to = edg[nown][i].to;
		if(to == fa || vis[to]) continue;
		query(to, nown, dis + edg[nown][i].dis, w + 1);
	}
	return;
}
void update(int nown, int fa, int dis, int w) {
	if(dis > k) return;
	buk[dis] = min(buk[dis], w);
	for(int i = 0, to; i < edg[nown].size(); i++) {
		to = edg[nown][i].to;
		if(to == fa || vis[to]) continue;
		update(to, nown, dis + edg[nown][i].dis, w + 1);
	}
	return;
}
void dfs(int nown) {
	buk[0] = 0, vis[nown] = 1;
	for(int i = 0, to; i < edg[nown].size(); i++) {
		to = edg[nown][i].to;
		if(vis[to]) continue;
		query(to, nown, edg[nown][i].dis, 1);
		update(to, nown, edg[nown][i].dis, 1);
	}
	clear(nown, 0, 0);
	for(int i = 0, to; i < edg[nown].size(); i++) {
		to = edg[nown][i].to;
		if(vis[to]) continue;
		rt = 0, siz[0] = siz[to], getRt(to, nown), dfs(rt);
	}
	return;
}
int main() {
	cin >> n >> k;
	for(int i = 1; i < n; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		++tmpx, ++tmpy;
		edg[tmpx].push_back(EDGE{tmpy, tmpz});
		edg[tmpy].push_back(EDGE{tmpx, tmpz});
	}
	for(int i = 0; i <= k; i++) buk[i] = 1e9;
	rt = 0, siz[0] = msiz[0] = n, getRt(1, 0), dfs(rt);
	if(ans == 1e9) ans = -1;
	cout << ans << endl;
	return 0;
}