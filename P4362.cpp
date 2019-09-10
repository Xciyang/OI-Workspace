#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define int long long
int n, m, k, tmpx, tmpy, tmpz, head[301], edptr= 1;
struct edge {
	int to, nexty, dis;
} eds[1001];
void add(int a, int b, int c) {
	eds[edptr].to= b, eds[edptr].nexty= head[a], eds[edptr].dis= c;
	head[a]= edptr++;
	return;
}
int f[301][301][2], tmpf[301][2];
void dfs(int nown, int fa) {
	f[nown][1][1]= f[nown][0][0]= 0;
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == fa) continue;
		dfs(to, nown);
		memset(tmpf, 0x3f, sizeof(tmpf));
		for(int j= 0; j <= k; j++) {
			for(int l= 0; l <= j; l++) {
				tmpf[j][0]= min(tmpf[j][0], min(f[nown][l][0] + f[to][j - l][0] + (m == 2) * eds[i].dis, f[nown][l][0] + f[to][j - l][1]));
				tmpf[j][1]= min(tmpf[j][1], min(f[nown][l][1] + f[to][j - l][1] + eds[i].dis, f[nown][l][1] + f[to][j - l][0]));
			}
		}
		memcpy(f[nown], tmpf, sizeof(f[nown]));
	}
	return;
}
signed main() {
	cin >> n >> m >> k;
	for(int i= 1; i < n; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		add(tmpx, tmpy, tmpz), add(tmpy, tmpx, tmpz);
	}
	if(n - k < m - 1) {
		cout << -1 << endl;
		return 0;
	}
	memset(f, 0x3f, sizeof(f));
	dfs(1, 0);
	cout << f[1][k][1] << endl;
	return 0;
}