#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#include <string.h>
#include <limits.h>
#include <vector>
using namespace std;
int n, m, h, a[400005], num[400005], t1, t2, tmps, cir[400005], f[400005][20];
vector< int > cirs[400005];
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
inline int qpow(int A, int B, int p) {
	int ans= 1;
	while(B) {
		if(B & 1) ans= (long long)ans * A % p;
		A= (long long)A * A % p, B>>= 1;
	}
	return ans;
}
inline int mpow(int A, int B) {
	if(A == 1) return 1;
	long long ans= 1;
	while(B--) {
		ans= ans * A;
		if(ans > n) return -1;
	}
	return ans;
}
inline int getf(int x, int k) {
	for(int i= 19; i >= 0; i--)
		if((1 << i) & k) x= f[x][i];
	return x;
}

int main() {
	read(n);
	for(int i= 1; i <= n; i++) read(f[i][0]);
	for(int j= 1; j < 20; j++)
		for(int i= 1; i <= n; i++) f[i][j]= f[f[i][j - 1]][j - 1];
	for(int i= 1; i <= n; i++) {
		if(!cir[f[i][19]]) ++h;
		for(int j= f[i][19]; !cir[j]; j= f[j][0]) cir[j]= h, num[j]= cirs[h].size(), cirs[h].push_back(j);
	}
	read(m);
	for(int i= 1; i <= m; i++) {
		read(tmps), read(t1), read(t2);
		int tmpx= mpow(t1, t2);
		if(tmpx == -1) {
			tmps= getf(tmps, n);
			int siz= cirs[cir[tmps]].size();
			put(cirs[cir[tmps]][((num[tmps] + qpow(t1, t2, siz) - n) % siz + siz) % siz]), putchar('\n');
		}
		else {
			put(getf(tmps, tmpx)), putchar('\n');
		}
	}
	return 0;
}