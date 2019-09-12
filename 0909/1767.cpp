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
int n, k, tmpx, c[256];
long long f[305][305][256], w[256], tmp[2];
int main() {
	read(n), read(k);
	memset(f, ~0x3f, sizeof(f));
	for(int i= 1; i <= n; i++) read(tmpx), f[i][i][tmpx]= 0;
	for(int i= 0; i < (1 << k); i++) read(c[i]), read(w[i]);
	for(int d= 2; d <= n; d++) {
		for(int i= 1, j= i + d - 1; j <= n; i++, j++) {
			int el= (d - 1) % (k - 1);
			if(!el) el= k - 1;
			for(int l= j; l > i; l-= k - 1)
				for(int s= 0; s < (1 << el); s++) f[i][j][s << 1]= max(f[i][j][s << 1], f[i][l - 1][s] + f[l][j][0]), f[i][j][s << 1 | 1]= max(f[i][j][s << 1 | 1], f[i][l - 1][s] + f[l][j][1]);
			if(el == k - 1) {
				memset(tmp, ~0x3f, sizeof(tmp));
				for(int s= 0; s < (1 << k); s++) tmp[c[s]]= max(tmp[c[s]], f[i][j][s] + w[s]);
				f[i][j][0]= tmp[0], f[i][j][1]= tmp[1];
			}
		}
	}
	memset(tmp, ~0x3f, sizeof(tmp));
	for(int s= 0; s < (1 << k); s++) tmp[0]= max(tmp[0], f[1][n][s]);
	cout << tmp[0] << endl;
	return 0;
}