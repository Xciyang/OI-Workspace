#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
#define int long long
int n, c[200005], tmpx, tmpy, tmpz;
struct EDGE {
	int to, dis;
};
vector< EDGE > edg[200005];
int f[200005], siz[200005], fa[200005];
long long ans, g[200005], res;
long long dfs(int nown) {
	siz[nown]= c[nown];
	long long tot= 0;
	for(int i= 0, to; i < edg[nown].size(); i++) {
		to= edg[nown][i].to;
		if(to == fa[nown]) continue;
		fa[to]= nown, tot+= dfs(to) + siz[to] * edg[nown][i].dis;
		siz[nown]+= siz[to];
	}
	return tot;
}
void dfs2(int nown) {
	for(int i= 0, to; i < edg[nown].size(); i++) {
		to= edg[nown][i].to;
		if(to == fa[nown]) continue;
		g[to]= g[nown] + (siz[1] - siz[to]) * edg[nown][i].dis - siz[to] * edg[nown][i].dis;
		dfs2(to);
	}
	return;
}
signed main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> c[i];
	for(int i= 1; i < n; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(EDGE{tmpy, 1}), edg[tmpy].push_back(EDGE{tmpx, 1});
	}
	ans= dfs(1);
	dfs2(1);
	for(int i= 1; i <= n; i++) res= max(res, g[i]);
	cout << ans + res << endl;
	return 0;
}