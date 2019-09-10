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
int n, k, tmpx, c[20], xy[20][10], last[31];
long long f[305][305][2], w[260], inf, bestans;
long long dfs(int l, int r, int ss, int di) {
	if(di == k - 1) return f[l][r][xy[ss][di]];
	long long res= inf, tmpt;
	for(int i= l; i <= r; i++) {
		if(f[l][i][xy[ss][di]] != inf) {
			tmpt= dfs(i + 1, r, ss, di + 1);
			if(tmpt == inf) continue;
			res= max(res, f[l][i][xy[ss][di]] + tmpt);
		}
	}
	return res;
}
int main() {
	read(n), read(k);
	memset(f, ~0x3f, sizeof(f)), inf= f[0][0][0];
	for(int i= 1; i <= n; i++) read(tmpx), f[i][i][tmpx]= 0;
	for(int i= 0; i < (k << 1); i++) read(c[i]), read(w[i]);
	if(n < k) {
		put(0), putchar('\n');
		return 0;
	}
	for(int s= 0; s < (k << 1); s++)
		for(int i= 0; i < k; i++) xy[s][i]= (s >> (k - i - 1)) & 1;
	for(int i= 1, j; i <= n - k + 1; i++) {
		for(int s= 0; s < (k << 1); s++) {
			for(j= i; j <= i + k - 1; j++)
				if(f[j][j][xy[s][j - i]] == inf) break;
			if(j == i + k) f[i][i + k - 1][c[s]]= w[s];
			bestans= max(bestans, w[s]);
		}
	}
	for(int d= k + 1; d <= n; d++) {
		for(int i= 1; i + d - 1 <= n; i++) {
			for(int j= 0; j < (k << 1); j++) {
				long long tmpt= dfs(i, i + d - 1, j, 0);
				if(tmpt == inf) continue;
				f[i][i + d - 1][c[j]]= max(f[i][i + d - 1][c[j]], tmpt + w[j]);
				bestans= max(bestans, tmpt + w[j]);
			}
		}
	}
	put(bestans), putchar('\n');
	return 0;
}