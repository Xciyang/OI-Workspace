#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
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
int t, n, m, head[100005], edptr, tmpx, tmpy, tmpz;
struct EDGE {
	int to, nexty, color;
} eds[400005];
void add(int a, int b, int c) {
	eds[edptr].to= b, eds[edptr].nexty= head[a], eds[edptr].color= c;
	head[a]= edptr++;
	return;
}
int dis1[100005], dis2[100005], minx[100005];
queue< int > qu;
void BFS(int *dis, int st) {
	dis[st]= 0;
	register int nown;
	qu.push(st);
	while(!qu.empty()) {
		nown= qu.front(), qu.pop();
		for(int i= head[nown], to; i; i= eds[i].nexty) {
			to= eds[i].to;
			if(dis[to] > dis[nown] + 1) qu.push(to), dis[to]= dis[nown] + 1;
		}
	}
	return;
}
int ans[100005], zdl[100005], wp[100005];
int main() {
	read(t);
	while(t--) {
		read(n), read(m), edptr= 1;
		memset(head, 0, sizeof(head)), memset(zdl, 0, sizeof(zdl));
		memset(dis1, 0x3f, sizeof(dis1)), memset(dis2, 0x3f, sizeof(dis2));
		memset(minx, 0x3f, sizeof(minx)), memset(ans, 0x3f, sizeof(ans));
		memset(wp, 0, sizeof(wp));
		for(int i= 1; i <= m; i++) {
			read(tmpx), read(tmpy), read(tmpz);
			add(tmpx, tmpy, tmpz), add(tmpy, tmpx, tmpz);
		}
		BFS(dis1, 1), BFS(dis2, n), put(dis1[n]), putchar('\n');
		for(int i= 1; i <= n; i++)
			if(dis1[i] + dis2[i] == dis1[n]) zdl[i]= 1;
		qu.push(1), wp[1]= 1;
		register int nown;
		while(!qu.empty()) {
			nown= qu.front(), qu.pop();
			if(minx[nown] > ans[dis1[nown]]) continue;
			for(int i= head[nown], to; i; i= eds[i].nexty) {
				to= eds[i].to;
				if(!zdl[to] || dis1[nown] + 1 != dis1[to]) continue;
				minx[to]= min(minx[to], eds[i].color), ans[dis1[to]]= min(ans[dis1[to]], eds[i].color);
				if(!wp[to]) wp[to]= 1, qu.push(to);
			}
		}
		for(int i= 1; i <= dis1[n]; i++) put(ans[i]), putchar(' ');
		putchar('\n');
	}
	return 0;
}
