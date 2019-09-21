#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int n, m, nowans, b[400005], tmpx, tmpy, k, a[400005], ans[400005], f[400005];
vector< int > edg[400005];
inline int getf(int x) {
	return f[x] == x ? x : f[x]= getf(f[x]);
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy, ++tmpx, ++tmpy;
		edg[tmpx].push_back(tmpy);
		edg[tmpy].push_back(tmpx);
	}
	cin >> k;
	for(int i= 1; i <= k; i++) cin >> a[i], ++a[i], b[a[i]]= 1;
	for(int i= 1; i <= n; i++) f[i]= i, nowans+= 1 - b[i];
	int fx, fy;
	for(int i= 1; i <= n; i++) {
		if(b[i]) continue;
		fx= getf(i);
		for(int j= 0; j < edg[i].size(); j++) {
			if(b[edg[i][j]]) continue;
			fy= getf(edg[i][j]);
			if(fx == fy) continue;
			--nowans;
			f[fy]= fx;
		}
	}
	ans[k]= nowans;
	for(int i= k; i; i--) {
		b[a[i]]= 0, ++nowans;
		fx= getf(a[i]);
		for(int j= 0; j < edg[a[i]].size(); j++) {
			if(b[edg[a[i]][j]]) continue;
			fy= getf(edg[a[i]][j]);
			if(fx == fy) continue;
			--nowans;
			f[fy]= fx;
		}
		ans[i - 1]= nowans;
	}
	for(int i= 0; i <= k; i++) cout << ans[i] << endl;
	return 0;
}