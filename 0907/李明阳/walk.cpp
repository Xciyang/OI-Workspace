#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <stack>
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
struct edge1 {
	int nexty, x, y;
} eds[400005];
struct edge {
	int to, nexty;
} eds2[3000006];
int tmpx, tmpy, tmpz, head[1000006], edptr= 1, ans[1000006], tms, wp[400005], ml;
void add(int a, int x, int y) {
	eds[edptr].nexty= head[a], eds[edptr].x= x, eds[edptr].y= y;
	head[a]= edptr++;
	return;
}
int n, head2[400005], edptr2;
void add2(int x, int y) {
	eds2[edptr2].to= y, eds2[edptr2].nexty= head2[x];
	head2[x]= edptr2++;
	return;
}
int dfs(int nown) {
	wp[nown]= tms;
	int l= 0, r= 0;
	for(int i= head2[nown], to; i; i= eds2[i].nexty) {
		to= eds2[i].to;
		if(wp[to] == tms) continue;
		int res= dfs(to) + 1;
		if(res > l)
			r= l, l= res;
		else if(res > r)
			r= res;
	}
	ml= max(ml, l + r);
	return l;
}
int st[3000006];
int main() {
	read(n);
	for(int i= 1; i < n; i++) read(tmpx), read(tmpy), read(tmpz), add(tmpz, tmpx, tmpy);
	for(int i= 1; i <= 1000000; i++) {
		edptr2= 1;
		for(int j= i; j <= 1000000; j+= i)
			for(int k= head[j]; k; k= eds[k].nexty) add2(eds[k].x, eds[k].y), add2(eds[k].y, eds[k].x), st[++st[0]]= eds[k].x, st[++st[0]]= eds[k].y;
		++tms, ml= 0;
		for(int i= 1; i <= st[0]; i++) {
			if(wp[st[i]] != tms) dfs(st[i]);
			head2[st[i]]= 0;
		}
		st[0]= 0, ans[ml]= i;
	}
	for(int i= n; i; i--) ans[i]= max(ans[i], ans[i + 1]);
	for(int i= 1; i <= n; i++) put(ans[i]), putchar('\n');
	return 0;
}