#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
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
int n, tmpx, tmpy, tmpz, f[100005], siz[100005];
long long ans;
struct EDGE {
	int x, y, dis;
	inline int operator<(const EDGE &n2) const {
		return dis < n2.dis;
	}
} edg[100005];
inline int qf(int x) {
	return f[x] == x ? x : f[x]= qf(f[x]);
}
int main() {
	read(n);
	for(int i= 1; i <= n; i++) f[i]= i, siz[i]= 1;
	for(int i= 1; i < n; i++) {
		read(tmpx), read(tmpy), read(tmpz);
		edg[i].x= tmpx, edg[i].y= tmpy, ans+= edg[i].dis= tmpz;
	}
	sort(edg + 1, edg + n);
	for(int i= 1; i < n; i++) {
		int x= edg[i].x, y= edg[i].y, fx= qf(x), fy= qf(y);
		if(fx == fy) continue;
		ans+= (edg[i].dis + 1) * ((long long)siz[fx] * siz[fy] - 1);
		f[fy]= fx, siz[fx]+= siz[fy];
	}
	put(ans), putchar('\n');
	return 0;
}