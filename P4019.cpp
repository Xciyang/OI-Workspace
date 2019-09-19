#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int n, m, c, f[500005][11][11], vis[500005][11][11], b[500005][11], k[500005], tmpx, tmpy, tmpz, ans;
int dfs(int x, int ch, int bx);
int DFS(int x, int ch, int bx) {
	printf("-ENTER- %d %d %d\n", x, ch, bx);
	int res= dfs(x, ch, bx);
	printf("-EXIT- %d %d %d %d\n", x, ch, bx, res);
	return res;
}
int dfs(int x, int ch, int bx) {
	if(vis[x][ch][bx]) return f[x][ch][bx];
	vis[x][ch][bx]= 1;
	if(x == 1) {
		if(ch == bx || b[x][ch]) return 0;
		return f[x][ch][bx]= 1;
	}
	if(b[x][ch]) return 0;
	if(k[x]) return f[x][ch][bx]= dfs(x - 1, ch, bx);
	for(int i= 1; i <= c; i++) 
		if(i != ch) f[x][ch][bx]= (f[x][ch][bx] + dfs(x - 1, i, bx)) % 987654321;
	return f[x][ch][bx];
}
int main() {
	cin >> n >> m >> c;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		if(tmpx == 1)
			for(int j= 1; j <= c; j++)
				if(j != tmpz) b[tmpy][j]= 1;
		if(tmpx == 2) b[tmpy][tmpz]= 1;
		if(tmpx == 3) k[tmpy < tmpz ? tmpz : tmpy]= 1;
	}
	if(n == 1) {
		for(int i= 1; i <= c; i++) ans+= b[1][i];
		cout << ans << endl;
		return 0;
	}
	for(int i= 1; i <= c; i++) ans= (ans + dfs(n, i, i)) % 987654321;
	cout << ans << endl;
	return 0;
}