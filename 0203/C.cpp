#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int n, k, tmpx, tmpy, tmpz;
struct EDGE {
	int to, dis;
};
vector< EDGE > edg[200005];
int fa[200005][21], dep[200005], q[200005], c[200005];
long long dis[200005][21], ans;
void dfs(int nown) {
	dep[nown] = dep[fa[nown][0]] + 1;
	for(int i = 1; i < 21; i++) {
		fa[nown][i] = fa[fa[nown][i - 1]][i - 1];
		dis[nown][i] = dis[fa[nown][i - 1]][i - 1];
	}
	for(int i = 0, to; i < edg[nown].size(); i++) {
		to = edg[nown][i].to;
		if(to == fa[nown][0]) continue;
		fa[to][0] = nown, dis[to][0] = edg[nown][i].dis;
		dfs(to);
	}
	return;
}
long long getd(int x, int y) {
	if(!x || !y || x == y) return 0;
	long long res = 0;
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 20; i >= 0; i--) {
		if(dep[fa[x][i]] >= dep[y]) res += dis[x][i], x = fa[x][i];
	}
	if(x == y) return res;
	for(int i = 20; i >= 0; i--) {
		if(fa[x][i] != fa[y][i]) {
			res += dis[x][i] + dis[y][i];
			x = fa[x][i], y = fa[y][i];
		}
	}
	return res + dis[x][0] + dis[y][0];
}
void DFS(int nk, long long res) {
	if(nk == k + 1) {
        ans= max(ans, res + getd(c[1], c[k]));
        return;
	}
	for(int i = 1; i <= n; i++) {
		if(q[i]) continue;
		q[i] = 1, c[nk] = i;
		DFS(nk + 1, res + getd(c[nk - 1], c[nk]));
		q[i] = 0, c[nk] = 0;
	}
}
int main() {
	cin >> n >> k;
	for(int i = 1; i < n; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		edg[tmpx].push_back(EDGE{tmpy, tmpz});
		edg[tmpy].push_back(EDGE{tmpx, tmpz});
	}
	dfs(1);
	DFS(1, 0);
	cout << ans << endl;
	return 0;
}