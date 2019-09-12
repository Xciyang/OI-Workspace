#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define file(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)
using namespace std;
template < typename T >
inline void read(T &e) {
	e= 0;
	T f= 1;
	char ch= getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') e= e * 10 + ch - '0', ch= getchar();
	e*= f;
	return;
}
template < typename T >
inline int put(const T &e) {
	if(e < 0) return putchar('-'), put(-e);
	if(e > 9) put(e / 10);
	return putchar('0' + e % 10);
}
int n, A, B, f[55][55][55][55], w[55], vis[55][55][55][55], ls[55], dy[55], lscnt, tmpx, tmpy, Q[55][55];
int dfs(int l, int r, int ml, int mr) {
	if(vis[l][r][ml][mr]) return f[l][r][ml][mr];
	f[l][r][ml][mr]= 0x3f3f3f3f, vis[l][r][ml][mr]= 1;
	if(ml + mr) {
		if(l == r) {
			if(ml <= dy[l] && dy[l] <= mr) f[l][r][ml][mr]= 0;
		}
		else {
			for(int i= l; i < r; i++) {
				f[l][r][ml][mr]= min(f[l][r][ml][mr], dfs(l, i, ml, mr) + dfs(i + 1, r, ml, mr));
				f[l][r][ml][mr]= min(f[l][r][ml][mr], dfs(l, i, 0, 0) + dfs(i + 1, r, ml, mr));
				f[l][r][ml][mr]= min(f[l][r][ml][mr], dfs(l, i, ml, mr) + dfs(i + 1, r, 0, 0));
			}
		}
	}
	else {
		int maxx= 0, minx= 0x3f3f3f3f;
		for(int i= l; i <= r; i++) maxx= max(maxx, w[i]), minx= min(minx, w[i]);
		f[l][r][0][0]= A + B * (maxx - minx) * (maxx - minx);
		for(int i= 1; i <= lscnt; i++)
			for(int j= i; j <= lscnt; j++) f[l][r][0][0]= min(f[l][r][0][0], dfs(l, r, i, j) + A + B * (ls[j] - ls[i]) * (ls[j] - ls[i]));
	}
	return f[l][r][ml][mr];
}
int main() {
	read(n), read(A), read(B);
	for(int i= 1; i <= n; i++) read(w[i]), ls[i]= w[i];
	sort(ls + 1, ls + n + 1);
	lscnt= unique(ls + 1, ls + n + 1) - ls - 1;
	for(int i= 1; i <= n; i++) dy[i]= lower_bound(ls + 1, ls + lscnt + 1, w[i]) - ls;
	cout << dfs(1, n, 0, 0) << endl;
	return 0;
}