#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int n, k, dis[50005], buk[505], tmpx, tmpy;
vector< int > edg[50005];
int siz[50005], rt, vis[50005], msiz[50005];
void getRt(int nown, int fa) {
	register int to;
	msiz[nown] = 0, siz[nown] = 1;
	for(int i = 0; i < edg[nown].size(); i++) {
		to = edg[nown][i];
		if(to == fa || vis[to]) continue;
		getRt(to, nown);
		siz[nown] += siz[to], msiz[nown] = max(msiz[nown], siz[to]);
	}
	msiz[nown] = max(msiz[nown], siz[0] - siz[nown]);
	if(msiz[nown] < msiz[rt]) rt = nown;
	return;
}
long long ans = 0;
void getd(int nown, int fa) {
	register int to;
	dis[nown] = dis[fa] + 1;
	if(dis[nown] > k) return;
	++buk[dis[nown]];
	for(int i = 0; i < edg[nown].size(); i++) {
		to = edg[nown][i];
		if(to == fa || vis[to]) continue;
		getd(to, nown);
	}
	return;
}
long long solve(int nown, int pre) {
	for(int i = 0; i <= k; i++) buk[i] = 0;
	dis[0] = pre;
	getd(nown, 0);
	long long res = 0;
	for(int i = 0; i <= k / 2; i++) {
		if(i * 2 == k) {
			res += 1ll * buk[i] * (buk[i] - 1) / 2;
		}
		else {
			res += 1ll * buk[i] * buk[k - i];
		}
	}
	return res;
}
void dfs(int nown) {
	vis[nown] = 1, ans += solve(nown, -1);
	register int to;
	for(int i = 0; i < edg[nown].size(); i++) {
		to = edg[nown][i];
		if(vis[to]) continue;
		ans -= solve(to, 0);
		rt = 0, siz[0] = siz[to];
		getRt(to, nown), dfs(rt);
	}
	return;
}

int main() {
	cin >> n >> k;
	for(int i = 1; i < n; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(tmpy);
		edg[tmpy].push_back(tmpx);
	}
	siz[0] = n, msiz[0] = 0x3f3f3f3f;
	getRt(1, 0), dfs(rt);
	cout << ans << endl;
	return 0;
}