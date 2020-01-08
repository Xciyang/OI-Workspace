#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, k, N, cont[1 << 16], p[105], pre[105], tmpx;
int vis[105][1 << 16];
double f[105][1 << 16], ans;
inline int count(int x) {
	return x ? count(x - (x & -x)) + 1 : 0;
}
double dfs(int wk, int s) {
	if(vis[wk][s]) return f[wk][s];
	vis[wk][s] = 1;
	if(wk > k) return f[wk][s] = 0;
	for(int i = 1; i <= n; i++) {
		if((s & pre[i]) == pre[i])
			f[wk][s] += max(dfs(wk + 1, s), dfs(wk + 1, s | (1 << (i - 1))) + p[i]);
		else
			f[wk][s] += dfs(wk + 1, s);
	}
	return f[wk][s] = f[wk][s] / n;
}
int main() {
	cin >> k >> n;
	for(int i = 1; i <= n; i++) {
		cin >> p[i];
		while(cin >> tmpx) {
			if(tmpx == 0) break;
			pre[i] |= (1 << (tmpx - 1));
		}
	}
	printf("%.6lf\n", dfs(1, 0));
	return 0;
}