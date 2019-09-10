#include <iostream>
#include <stdio.h>
#include <vector>
#define int long long
using namespace std;
int n, m, p[100005], tmpx, tmpy, tmpz, tmpk, fa[100005][20], dep[100005];
char typ[5];
vector< int > edg[100005];
int dp[100005][2];
void dfs1(int nown) {
	dep[nown]= dep[fa[nown][0]] + 1, dp[nown][1]= p[nown];
	for(int i= 1; i < 20; i++) fa[nown][i]= fa[fa[nown][i - 1]][i - 1];
	for(int i= 0, to; i < edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa[nown][0]) continue;
		fa[to][0]= nown, dfs1(to);
		dp[nown][0]+= dp[to][1], dp[nown][1]+= min(dp[to][0], dp[to][1]);
	}
	return;
}
int f[100005][2][20][2];  // i 0/1 2^i 0/1
void dfs2(int nown) {
	f[nown][0][0][0]= 100000000000000, f[nown][1][0][0]= dp[fa[nown][0]][0] - dp[nown][1], f[nown][0][0][1]= f[nown][1][0][1]= dp[fa[nown][0]][1] - min(dp[nown][1], dp[nown][0]);
	for(int i= 1, nowf; (1 << i) < dep[nown]; i++) {
		nowf= fa[nown][i - 1];
		f[nown][0][i][0]= min(f[nown][0][i - 1][0] + f[nowf][0][i - 1][0], f[nown][0][i - 1][1] + f[nowf][1][i - 1][0]);
		f[nown][0][i][1]= min(f[nown][0][i - 1][0] + f[nowf][0][i - 1][1], f[nown][0][i - 1][1] + f[nowf][1][i - 1][1]);
		f[nown][1][i][0]= min(f[nown][1][i - 1][0] + f[nowf][0][i - 1][0], f[nown][1][i - 1][1] + f[nowf][1][i - 1][0]);
		f[nown][1][i][1]= min(f[nown][1][i - 1][0] + f[nowf][0][i - 1][1], f[nown][1][i - 1][1] + f[nowf][1][i - 1][1]);
	}
	for(int i= 0, to; i < edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa[nown][0]) continue;
		dfs2(to);
	}
	return;
}
int query(int x, int c1, int y, int c2) {
	if(dep[x] < dep[y]) swap(x, y), swap(c1, c2);
	int res, last0= 100000000000000, last1= 100000000000000, l0, l1;
	c1 ? last1= dp[x][1] : last0= dp[x][0];
	for(int i= 19; i >= 0; i--)
		if(dep[fa[x][i]] >= dep[y]) {
			l0= last0, l1= last1;
			last0= min(l0 + f[x][0][i][0], l1 + f[x][1][i][0]), last1= min(l0 + f[x][0][i][1], l1 + f[x][1][i][1]);
			x= fa[x][i];
		}
	if(x != y) {
		int ly0= 100000000000000, ly1= 100000000000000;
		c2 ? ly1= dp[y][1] : ly0= dp[y][0];
		for(int i= 19; i >= 0; i--)
			if(fa[x][i] != fa[y][i]) {
				l0= last0, l1= last1;
				last0= min(l0 + f[x][0][i][0], l1 + f[x][1][i][0]), last1= min(l0 + f[x][0][i][1], l1 + f[x][1][i][1]);
				l0= ly0, l1= ly1;
				ly0= min(l0 + f[y][0][i][0], l1 + f[y][1][i][0]), ly1= min(l0 + f[y][0][i][1], l1 + f[y][1][i][1]);
				x= fa[x][i], y= fa[y][i];
			}
		l0= last0, l1= last1;
		last0= dp[fa[x][0]][0] - dp[x][1] - dp[y][1] + l1 + ly1, last1= dp[fa[x][0]][1] - min(dp[x][0], dp[x][1]) - min(dp[y][0], dp[y][1]) + min(l0, l1) + min(ly0, ly1);
		x= fa[x][0];
	}
	else
		c2 ? last0= 100000000000000 : last1= 100000000000000;
	if(x != 1) {
		for(int i= 19; i >= 0; i--)
			if(dep[fa[x][i]] >= dep[1]) {
				int l0= last0, l1= last1;
				last0= min(l0 + f[x][0][i][0], l1 + f[x][1][i][0]), last1= min(l0 + f[x][0][i][1], l1 + f[x][1][i][1]);
				x= fa[x][i];
			}
	}
	res= min(last0, last1);
	return res < 100000000000000 ? res : -1;
}
signed main() {
	scanf("%lld%lld%s", &n, &m, typ);
	for(int i= 1; i <= n; i++) scanf("%lld", p + i);
	for(int i= 1; i < n; i++) {
		scanf("%lld%lld", &tmpx, &tmpy);
		edg[tmpx].push_back(tmpy), edg[tmpy].push_back(tmpx);
	}
	dfs1(1), dfs2(1);
	while(m--) {
		scanf("%lld%lld%lld%lld", &tmpx, &tmpy, &tmpz, &tmpk);
		printf("%lld\n", query(tmpx, tmpy, tmpz, tmpk));
	}
	return 0;
}