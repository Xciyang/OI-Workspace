#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int n, m, tmpx, tmpy, tmpz, tmpk, w[300005], dep[300005], fa[300005][20];
vector< int > edg[300005];
void dfs1(int nown, int f) {
	fa[nown][0]= f, dep[nown]= dep[f] + 1;
	for(int i= 1; i < 20; i++) fa[nown][i]= fa[fa[nown][i - 1]][i - 1];
	for(int i= 0, to; i < edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == f) continue;
		dfs1(to, nown);
	}
	return;
}
int LCA(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i= 19; i >= 0; i--)
		if(dep[fa[x][i]] >= dep[y]) x= fa[x][i];
	if(x == y) return x;
	for(int i= 19; i >= 0; i--)
		if(fa[x][i] != fa[y][i]) x= fa[x][i], y= fa[y][i];
	return fa[x][0];
}
struct OP {
	int opt, v, c;
};
int upp[600005], unused[600005], *doww, ans[300005];
vector< OP > ops[300005];
void dfs2(int nown) {
	int lasta= upp[dep[nown] + w[nown]] + doww[dep[nown] - w[nown]];
	for(int i= 0; i < ops[nown].size(); i++) {
		if(ops[nown][i].opt) {
			doww[ops[nown][i].v]+= ops[nown][i].c;
		}
		else {
			upp[ops[nown][i].v]+= ops[nown][i].c;
		}
	}
	for(int i= 0, to; i < edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa[nown][0]) continue;
		dfs2(to);
	}
	ans[nown]= upp[dep[nown] + w[nown]] + doww[dep[nown] - w[nown]] - lasta;
	return;
}
int main() {
	doww= unused + 300000;
	cin >> n >> m;
	for(int i= 1; i < n; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(tmpy), edg[tmpy].push_back(tmpx);
	}
	for(int i= 1; i <= n; i++) cin >> w[i];
	dfs1(1, 0);
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy, tmpk= LCA(tmpx, tmpy);
		tmpz= dep[tmpx] + dep[tmpy] - 2 * dep[tmpk] + 1;
		ops[tmpx].push_back(OP{0, dep[tmpx], 1});
		ops[tmpk].push_back(OP{0, dep[tmpx], -1});
		ops[tmpy].push_back(OP{1, dep[tmpy] - tmpz + 1, 1});
		ops[fa[tmpk][0]].push_back(OP{1, dep[tmpy] - tmpz + 1, -1});
	}
	dfs2(1);
	for(int i= 1; i <= n; i++) cout << ans[i] << ' ';
	cout << endl;
	return 0;
}