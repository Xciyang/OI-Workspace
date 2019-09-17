#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <stdlib.h>
#include <time.h>
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
int t, n, a[100005], p, len;
int main() {
	file("book");
	read(t);
	while(t--) {
		read(n);
		for(int i= 1; i <= n; i++) read(a[i]);
		while(n && a[n] == n) --n;
		if(!n) {
			put(0), putchar('\n');
			continue;
		}
		for(len= p= 1; p <= n; p++)
			if(a[p] == n) break;
		while(p - 1&& a[p - 1] == a[p + 1] - 1) --p, ++len;
		put(n - len), putchar('\n');
	}
	return 0;
}
