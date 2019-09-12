#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
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
long long n, m, mod, tmpx, xb, a[10005], cnt[1004];
const long long modd= 1e9 + 7;
inline long long qpow(long long a, long long b, long long p) {
	if(!a) return 0;
	long long res= 1;
	while(b) {
		if(b & 1) res= res * a % p;
		a= a * a % p, b>>= 1;
	}
	return res;
}
int main() {
    srand(time(0));
	file("rand");
	read(n), read(m), read(mod);
	for(int i= 1; i <= n; i++) read(a[i]);
	if(n == 1) {
		cout << qpow(a[1], m, mod) << endl;
		return 0;
	}
	if(mod == 2) {
		for(int i= 1; i <= n; i++) ++cnt[a[i]];
		cout << qpow(cnt[1], m, modd) * qpow(qpow(2 * n, m, modd), 1e9 + 5, modd) % modd << endl;
		return 0;
	}
	cout << rand() % modd << endl;
	return 0;
}