#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <map>
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
inline long long absl(long long x) {
	return x < 0 ? -x : x;
}
int n, L, R, s, ans2[200005], tmp[200005];
long long x[200005], ans;
int c[200005];
void dfs(int nown, int g, long long nownans) {
	if(nownans >= ans) return;
	if(g == n) {
		ans= nownans, memcpy(ans2, tmp, sizeof(ans2));
		return;
	}
	if(L) {
		for(int i= nown - 1; i; i--) {
			if(!c[i]) {
				c[i]= 1, --L, tmp[g]= i;
				dfs(i, g + 1, nownans + x[nown] - x[i]);
				c[i]= 0, ++L;
			}
		}
	}
	if(R) {
		for(int i= nown + 1; i <= n; i++) {
			if(!c[i]) {
				c[i]= 1, --R, tmp[g]= i;
				dfs(i, g + 1, nownans + x[i] - x[nown]);
				c[i]= 0, ++R;
			}
		}
	}
	return;
}
int main() {
	file("travel");
	read(n), read(L), read(s), R= n - L - 1;
	for(int i= 1; i <= n; i++) read(x[i]);
	ans= 1e15, c[s]= 1, dfs(s, 1, 0);
	put(ans), putchar('\n');
	for(int i= 1; i < n; i++) put(ans2[i]), putchar(' ');
	putchar('\n');
	return 0;
}