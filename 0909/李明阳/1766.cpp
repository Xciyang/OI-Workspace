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
int n, A, B, f[55][55], w[55], maxq[55][55], minq[55][55], tmpx, tmpy;
int main() {
	read(n), read(A), read(B);
	for(int i= 1; i <= n; i++) read(w[i]);
	if(n == 1) {
		put(A), putchar('\n');
		return 0;
	}
	if(n == 2) {
		put(min(2 * A, A + B * (w[2] - w[1]) * (w[2] - w[1]))), putchar('\n');
		return 0;
	}
	for(int i= 1; i <= n; i++) {
		for(int j= i; j <= n; j++) {
			minq[i][j]= 0x3f3f3f3f;
			for(int k= i; k <= j; k++) maxq[i][j]= max(maxq[i][j], w[k]), minq[i][j]= min(minq[i][j], w[k]);
			f[i][j]= A + B * (maxq[i][j] - minq[i][j]) * (maxq[i][j] - minq[i][j]);
		}
	}
	for(int l= 2; l <= n; l++) {
		for(int i= 1, j= i + l - 1; j <= n; i++, j++) {
			for(int k= i; k < j; k++) f[i][j]= min(f[i][j], f[i][k] + f[k + 1][j]);
			for(int k= i + 1; k < j; k++) {
				for(int d= i; d < j; d++) {
					tmpx= max(maxq[i][k - 1], maxq[d + 1][j]), tmpy= min(minq[i][k - 1], minq[d + 1][j]);
					f[i][j]= min(f[i][j], f[k][d] + A + B * (tmpx - tmpy) * (tmpx - tmpy));
				}
			}
		}
	}
	cout << f[1][n] << endl;
	return 0;
}