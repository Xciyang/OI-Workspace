#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
const long long p= 45989;
int n, m, A, B, tmpx, tmpy, edptr= 2, head[505];
struct EDGE {
	int to, nexty;
} edg[505];
void add(int a, int b) {
	edg[edptr].nexty= head[a], edg[edptr].to= b;
	head[a]= edptr++;
	return;
}
struct MAT {
	long long a[200][200];
} base, res;
long long t, ans;
MAT mul(const MAT &a, const MAT &b, int c, int c2, int c3) {
	MAT r;
	memset(&r, 0, sizeof(r));
	for(int i= 1; i <= c; i++)
		for(int j= 1; j <= c2; j++)
			for(int k= 1; k <= c3; k++) r.a[i][k]= (r.a[i][k] + a.a[i][j] * b.a[j][k]) % p;
	return r;
}
void qpow() {
	--t;
	while(t) {
		if(t & 1) res= mul(res, base, 1, edptr, edptr);
		base= mul(base, base, edptr, edptr, edptr), t>>= 1;
	}
	return;
}
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
int main() {
	read(n), read(m), read(t), read(A), read(B);
	++A, ++B;
	for(int i= 1; i <= m; i++) read(tmpx), read(tmpy), add(tmpx + 1, tmpy + 1), add(tmpy + 1, tmpx + 1);
	for(int i= 2, to; i <= edptr; i++) {
		to= edg[i].to;
		for(int j= head[to]; j; j= edg[j].nexty) {
			if((i ^ j) == 1) continue;
			++base.a[i][j];
		}
	}
	for(int i= head[A]; i; i= edg[i].nexty) ++res.a[1][i];
	qpow();
	for(int i= head[B]; i; i= edg[i].nexty) ans= (ans + res.a[1][i ^ 1]) % p;
	put(ans), putchar('\n');
	return 0;
}