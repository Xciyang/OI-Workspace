#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, a[88][88], nown, vis[88][88];
__int128_t ans, base;
int put(__int128_t i) {
	if(i < 0) return putchar('-'), put(-i);
	if(i > 9) put(i / 10);
	return putchar('0' + i % 10);
}
__int128_t f[88][88], pow2[88];
__int128_t dfs(int l, int r) {
	if(vis[l][r] == nown) return f[l][r];
	vis[l][r]= nown;
	if(l == r) return f[l][r]= (__int128_t)a[nown][l] * pow2[m];
	return f[l][r]= max(dfs(l + 1, r) + pow2[m - (r - l)] * a[nown][l], dfs(l, r - 1) + pow2[m - (r - l)] * a[nown][r]);
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++)
		for(int j= 1; j <= m; j++) cin >> a[i][j];
	pow2[0]= 1;
	for(int i= 1; i <= m; i++) pow2[i]= pow2[i - 1] * 2;
	for(int i= 1; i <= n; i++) nown= i, ans+= dfs(1, m);
	put(ans);
	return 0;
}