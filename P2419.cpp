#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, g[105][105], tmpx, tmpy, ans;
int main() {
	cin >> n >> m;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy;
		g[tmpx][tmpy]= 1;
	}
	for(int i= 1; i <= n; i++)
		for(int j= 1; j <= n; j++)
			for(int k= 1; k <= n; k++) g[j][k]|= (g[j][i] & g[i][k]);
	for(int i= 1, j; i <= n; i++) {
		for(j= 1; j <= n; j++) {
			if(i == j) continue;
			if(!g[i][j] && !g[j][i]) break;
		}
		if(j == n + 1) ++ans;
	}
	cout << ans << endl;
	return 0;
}