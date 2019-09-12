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
int t, n, m, last[100005][2], head[100005], edptr, tmpx, tmpy, tmpz;
struct EDGE {
	int to, nexty, color;
} eds[400005];
void add(int a, int b, int c) {
	eds[edptr].to= b, eds[edptr].nexty= head[a], eds[edptr].color= c;
	head[a]= edptr++;
	return;
}
int dis[100005], wp[100005];
int check(int x, int y) {
	if(x == y) return 0;
	int res= check(last[x][0], last[y][0]);
	if(res) return res;
	return last[x][1] < last[y][1] ? -1 : (last[x][1] != last[y][1]);
}
queue< int > qu;
void BFS() {
	memset(wp, 0, sizeof(wp)), memset(dis, 0x3f, sizeof(dis)), dis[1]= 0, wp[1]= 1;
	register int nown;
	qu.push(1);
	while(!qu.empty()) {
		nown= qu.front(), qu.pop();
		for(int i= head[nown], to; i; i= eds[i].nexty) {
			to= eds[i].to;
			if(!wp[to]) qu.push(to), wp[to]= 1;
			if(dis[to] > dis[nown] + 1)
				dis[to]= dis[nown] + 1, last[to][0]= nown, last[to][1]= eds[i].color;
			else if(dis[to] == dis[nown] + 1 && check(last[to][0], nown) == 1)
				last[to][0]= nown, last[to][1]= eds[i].color;
		}
	}
	return;
}
int ans[100005], cnt;
int main() {
	read(t);
	while(t--) {
		read(n), read(m), edptr= 1, cnt= 0;
		memset(head, 0, sizeof(head));
		for(int i= 1; i <= m; i++) {
			read(tmpx), read(tmpy), read(tmpz);
			add(tmpx, tmpy, tmpz), add(tmpy, tmpx, tmpz);
		}
		BFS(), put(dis[n]), putchar('\n');
		for(int i= n; i != 1; i= last[i][0]) ans[++cnt]= last[i][1];
		for(int i= cnt; i; i--) put(ans[i]), putchar(' ');
		putchar('\n');
	}
	return 0;
}