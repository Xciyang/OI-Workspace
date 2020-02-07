#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int n, tmpx, tmpy, vis[5005];
vector< int > edg[5005];
const int p = 1e9 + 7;
int dfs(int nown, int fa) {
	if(vis[nown]) return 1;
	vis[nown] = 1;
	int res = 1, to;
	for(int i = 0; i < edg[nown].size(); i++) {
		to = edg[nown][i];
		if(vis[to]) continue;
		res = 1ll * res * dfs(to, to) % p;
	}
	vis[nown] = 0;
	for(int i = 0; i < edg[nown].size(); i++) {
		to = edg[nown][i];
		if(to == fa || vis[to]) continue;
		res = (1ll * res + dfs(to, nown)) % p;
	}
	return res;
}
int main() {
	cin >> n;
	for(int i = 1; i < n; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(tmpy);
		edg[tmpy].push_back(tmpx);
	}
	cout << dfs(1, 1) << endl;
	return 0;
}