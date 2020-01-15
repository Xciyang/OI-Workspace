#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
struct EDGE {
	int to, dis;
};
int n, k, tmpx, tmpy, tmpz;
vector< EDGE > edg[40005];
int siz[40005], rt, msiz[40005], vis[40005];
void getRoot(int nown, int fa) {
	siz[nown] = 1, msiz[nown] = 0;
	for(int i = 0, to; i < edg[nown].size(); i++) {
		to = edg[nown][i].to;
		if(to == fa || vis[to]) continue;
		getRoot(to, nown), siz[nown] += siz[to], msiz[nown] = max(msiz[nown], siz[to]);
	}
	msiz[nown] = max(msiz[nown], siz[0] - siz[nown]);
	if(msiz[nown] < msiz[rt]) rt = nown;
	return;
}
int dis[40005], buk[40005];
void getDis(int nown, int fa) {
	if(dis[nown] > k) return;
	buk[++buk[0]] = dis[nown];
	for(int i = 0, to; i < edg[nown].size(); i++) {
		to = edg[nown][i].to;
		if(to == fa || vis[to]) continue;
		dis[to] = dis[nown] + edg[nown][i].dis, getDis(to, nown);
	}
	return;
}
int ans;
int solve(int nown, int pdis) {
	buk[0] = 0, dis[nown] = pdis, getDis(nown, 0);
	sort(buk + 1, buk + buk[0] + 1);
	int l = 1, r = buk[0], res = 0;
	while(l <= r) {
		if(buk[l] + buk[r] <= k)
			res += r - l, ++l;
		else
			--r;
	}
	return res;
}
void dfs(int nown) {
	vis[nown] = 1, ans += solve(nown, 0);
	for(int i = 0, to; i < edg[nown].size(); i++) {
		to = edg[nown][i].to;
		if(vis[to]) continue;
		ans -= solve(to, edg[nown][i].dis);
		siz[0] = siz[to], rt = 0, getRoot(to, nown), dfs(rt);
	}
	return;
}
int main() {
	cin >> n;
	for(int i = 1; i < n; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		edg[tmpx].push_back(EDGE{tmpy, tmpz});
		edg[tmpy].push_back(EDGE{tmpx, tmpz});
	}
	cin >> k;
	msiz[0] = siz[0] = n, rt = 0, getRoot(1, 0), dfs(rt);
	cout << ans << endl;
	return 0;
}