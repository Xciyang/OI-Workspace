#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct YS {
	int t, x, y;
} ys[10005];
int n, m;
inline int absi(int x) {
	return x < 0 ? -x : x;
}
inline int DIS(int x1, int y1, int x2, int y2) {
	return absi(x1 - x2) + absi(y1 - y2);
}
int dis[10005], ans;
int main() {
	scanf("%d%d", &n, &m);
	for(register int i= 1; i <= m; i++) scanf("%d%d%d", &ys[i].t, &ys[i].x, &ys[i].y);
	for(register int i= m; i; i--) {
		int maxx= 0;
		for(register int j= m; j > i; j--)
			if(ys[j].t - ys[i].t >= DIS(ys[i].x, ys[i].y, ys[j].x, ys[j].y)) maxx= max(maxx, dis[j]);
		dis[i]= maxx + 1, ans= max(ans, dis[i]);
	}
	printf("%d\n", ans);
	return 0;
}