#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int n, dis[20005], tmpx, tmpy, tmpz;
struct EDGE {
	int to, dis;
};
vector< EDGE > edg[20005];
int siz[20005], rt, vis[20005], msiz[20005];
long long buk[4];
void getRt(int nown, int fa) {
	register int to;
	msiz[nown] = 0, siz[nown] = 1;
	for(int i = 0; i < edg[nown].size(); i++) {
		to = edg[nown][i].to;
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
	++buk[dis[nown] % 3];
	for(int i = 0; i < edg[nown].size(); i++) {
		to = edg[nown][i].to;
		if(to == fa || vis[to]) continue;
		dis[to] = dis[nown] + edg[nown][i].dis;
		getd(to, nown);
	}
	return;
}
long long solve(int nown, int pre) {
	for(int i = 0; i < 3; i++) buk[i] = 0;
	dis[nown] = pre;
	getd(nown, 0);
	return buk[1] * buk[2] * 2 + buk[0] * buk[0];
}
void dfs(int nown) {
	vis[nown] = 1, ans += solve(nown, 0);
	register int to;
	for(int i = 0; i < edg[nown].size(); i++) {
		to = edg[nown][i].to;
		if(vis[to]) continue;
		ans -= solve(to, edg[nown][i].dis);
		rt = 0, siz[0] = siz[to];
		getRt(to, nown), dfs(rt);
	}
	return;
}
inline long long gcd(long long a, long long b) {
	return b ? gcd(b, a % b) : a;
}
int main() {
	cin >> n;
	for(int i = 1; i < n; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		edg[tmpx].push_back(EDGE{tmpy, tmpz});
		edg[tmpy].push_back(EDGE{tmpx, tmpz});
	}
	siz[0] = n, msiz[0] = 0x3f3f3f3f;
	getRt(1, 0), dfs(rt);
	long long g = gcd(ans, n * n);
	cout << ans / g << '/' << n * n / g << endl;
	return 0;
}