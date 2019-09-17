#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <stdlib.h>
#include <math.h>
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
int T, n, m, w, npzptr, minp;
struct NODE {
	int x, y;
} mz[255];
struct TABLE {
	int r, c;
	bool operator<(const TABLE &t2) const {
		return r == t2.r ? c < t2.c : r > t2.r;
	}
	bool operator>(const TABLE &t2) const {
		return c < t2.c;
	}
} pz[255], npz[255];
int head[256][256], edptr;
struct EDGE {
	int tox, toy, dis, nexty;
} edg[2000006];
void add(int x, int y, int tox, int toy, int d) {
	edg[edptr].tox= tox, edg[edptr].toy= toy, edg[edptr].dis= d, edg[edptr].nexty= head[x][y];
	head[x][y]= edptr++;
	return;
}
queue< NODE > qu;
int wp[256][256], dis[256][256];
void SPFA() {
	memset(wp, 0, sizeof(wp)), memset(dis, 0x3f, sizeof(dis));
	wp[0][0]= 1, dis[0][0]= 0, qu.push(NODE{0, 0});
	register NODE nown;
	register int tox, toy;
	while(!qu.empty()) {
		nown= qu.front(), qu.pop();
		wp[nown.x][nown.y]= 0;
		for(int i= head[nown.x][nown.y]; i; i= edg[i].nexty) {
			tox= edg[i].tox, toy= edg[i].toy;
			if(dis[tox][toy] > dis[nown.x][nown.y] + edg[i].dis) {
				dis[tox][toy]= dis[nown.x][nown.y] + edg[i].dis;
				if(!wp[tox][toy]) wp[tox][toy]= 1, qu.push(NODE{tox, toy});
			}
		}
	}
	return;
}
int main() {
	read(T);
	while(T--) {
		read(n), read(m), read(w), edptr= 1, npzptr= 0, minp= 0x3f3f3f3f;
		memset(head, 0, sizeof(head));
		for(int i= 1; i <= n; i++) read(mz[i].x), read(mz[i].y);
		for(int i= 1; i <= m; i++) read(pz[i].r), read(pz[i].c);
		sort(pz + 1, pz + m + 1);
		for(int i= 1; i <= m; i++) {
			if(pz[i].c < minp) npz[++npzptr]= pz[i];
			minp= min(minp, pz[i].c);
		}
		sort(npz + 1, npz + npzptr + 1, greater< TABLE >());
		for(int i= 1; i <= n; i++) {
			for(int k= 1; k <= npzptr; k++) {
				if(mz[i].y - npz[k].r <= 0) add(0, 0, i, k, npz[k].c);
				if(mz[i].y + npz[k].r >= w) add(i, k, n + 1, m + 1, 0);
			}
			for(int k= 1; k < npzptr; k++) add(i, k, i, k + 1, npz[k + 1].c - npz[k].c);
			for(int j= 1; j <= n; j++) {
				if(i == j) continue;
				long long dis= ((long long)mz[i].x - mz[j].x) * (mz[i].x - mz[j].x) + ((long long)mz[i].y - mz[j].y) * (mz[i].y - mz[j].y);
				for(int k= npzptr, k2= 1; k; k--) {
					while(k2 <= npzptr && ((long long)npz[k].r + npz[k2].r) * (npz[k].r + npz[k2].r) < dis) ++k2;
					if(k2 > npzptr) break;
					add(i, k, j, k2, npz[k2].c);
				}
			}
		}
		SPFA();
		if(dis[n + 1][m + 1] == 0x3f3f3f3f)
			printf("impossible\n");
		else
			put(dis[n + 1][m + 1]), putchar('\n');
	}
	return 0;
}
/*
3
11 4 13
19 10
8 7
11 4
26 1
4 2
15 4
19 4
1 9
4 6
19 5
15 10
2 1
3 100
4 10000
5 1000000
11 4 13
19 10
8 7
11 4
26 1
4 2
15 4
19 4
1 9
4 6
19 5
15 10
2 1
3 2
4 3
5 4
1 1 1000000000
0 500000000
1 1

*/