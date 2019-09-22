#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
int n, tmpx, tmpy, f[1005], ans[1005], bestans;
vector< int > edg[1005];
int cmp(const int &x, const int &y) {
	return f[x] > f[y];
}
void dfs(int nown, int fa) {
	for(int i= 0, to; i < edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa) continue;
		dfs(to, nown);
	}
	sort(edg[nown].begin(), edg[nown].end(), cmp);
	f[nown]= 1;
	for(int i= 0; i < edg[nown].size() - (fa != 0); i++) f[nown]= max(f[nown], f[edg[nown][i]] + i + 1);
	return;
}
int main() {
	cin >> n;
	for(int i= 2; i <= n; i++) cin >> tmpx, edg[tmpx].push_back(i), edg[i].push_back(tmpx);
	bestans= n;
	for(int i= 1; i <= n; i++) {
		memset(f, 0, sizeof(f));
		dfs(i, 0);
		if(f[i] < bestans) ans[0]= 0, bestans= f[i];
		if(f[i] == bestans) ans[++ans[0]]= i;
	}
	cout << bestans << endl;
	for(int i= 1; i <= ans[0]; i++) cout << ans[i] << ' ';
	cout << endl;
	return 0;
}