#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, k, tmpx, tmpy, dep[100005], ls, rs, f[100005], ans;
vector< int > edg[100005];
void dfsLong(int nown, int fa, int &deppest) {
	f[nown]= fa, dep[nown]= dep[fa] + 1;
	if(dep[nown] > dep[deppest]) deppest= nown;
	for(int i= 0; i < edg[nown].size(); i++) {
		if(edg[nown][i] == fa) continue;
		dfsLong(edg[nown][i], nown, deppest);
	}
	return;
}
int todep[100005];
void dfsInit(int nown, int fa) {
	todep[nown]= dep[nown]= dep[fa] + 1;
	for(int i= 0, to, res; i < edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa) continue;
		dfsInit(to, nown), todep[nown]= max(todep[nown], todep[to]);
	}
	return;
}
struct NODE {
	int d, id;
	inline int operator<(const NODE &n2) const {
		return d > n2.d;
	}
} node[100005];
int cs[100005];
int main() {
	cin >> n >> k;
	for(int i= 1; i < n; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(tmpy), edg[tmpy].push_back(tmpx);
	}
	dfsLong(1, 0, ls), dfsLong(ls, 0, rs);
	int drs= (dep[rs]) / 2;
	while(drs--) rs= f[rs];
	dfsInit(rs, 0);
	for(int i= 1; i <= n; i++) node[i].id= i, node[i].d= todep[i] - dep[i];
	sort(node + 1, node + n + 1);
	for(int i= 1; i <= k; i++) cs[node[i].id]= 1;
	for(int i= 1; i <= n; i++)
		if(!cs[i]) ans= max(ans, todep[i] - dep[i] + 1);
	cout << ans << endl;
 	return 0;
}