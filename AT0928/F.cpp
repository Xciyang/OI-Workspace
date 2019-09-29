#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;
int n, m, tmpx, tmpy, r[1005], st[1005], ans[1005];
vector< int > edg[1005];
int dfs(int nown) {
	if(st[nown]) return 1;
	st[nown]= 1;
	for(int i= 0; i < edg[nown].size(); i++) {
		++r[edg[nown][i]];
		if(r[edg[nown][i]] > 1 && st[edg[nown][i]]) {
			for(int j= 0; j <= i; j++) --r[edg[nown][j]];
			st[nown]= 0;
			return 0;
		}
	}
	for(int i= 0; i < edg[nown].size(); i++) {
		if(r[edg[nown][i]] == 1 && dfs(edg[nown][i])) {
			ans[++ans[0]]= nown;
			return 1;
		}
	}
	for(int i= 0; i < edg[nown].size(); i++) --r[edg[nown][i]];
	st[nown]= 0;
	return 0;
}
int main() {
    srand(time(0));
	cin >> n >> m;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(tmpy);
	}
	while(clock() < CLOCKS_PER_SEC * 1.8)
		if(dfs(rand() % n + 1)) break;
	if(ans[0] == 0)
		cout << -1 << endl;
	else {
		cout << ans[0] << endl;
		sort(ans + 1, ans + ans[0] + 1);
		for(int i= 1; i <= ans[0]; i++) cout << ans[i] << endl;
	}
	return 0;
}