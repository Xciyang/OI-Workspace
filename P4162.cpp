#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <queue>
using namespace std;
int n, m, k;
inline int getp(int x, int y) {
	return (x - 1) * m + y;
}
struct EDGE {
	int x, dis;
};
char str[40][40];
int dis[905], moves[4][2]= {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
double D[905][905], ans;
vector< EDGE > edg[905];
queue< int > qu;
int wp[905];
void SPFA(int srcx, int srcy) {
	for(int i= 1; i <= n * m; i++) dis[i]= 0x3f3f3f3f, wp[i]= 0;
	int src= getp(srcx, srcy);
	dis[src]= (str[srcx][srcy] == '1'), wp[src]= 1;
	qu.push(src);
	register int nown, to;
	while(!qu.empty()) {
		nown= qu.front(), qu.pop(), ans= max(ans, D[src][nown]), wp[nown]= 0;
		for(int i= 0; i < edg[nown].size(); i++) {
			to= edg[nown][i].x;
			if(dis[to] > dis[nown] + edg[nown][i].dis) {
				dis[to]= dis[nown] + edg[nown][i].dis;
				if(!wp[to] && dis[to] <= k) qu.push(to);
			}
		}
	}
	return;
}
int main() {
	cin >> n >> m >> k;
	for(int i= 1; i <= n; i++) cin >> (str[i] + 1);
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) {
			for(int i2= 1; i2 <= n; i2++) {
				for(int j2= 1; j2 <= m; j2++) {
					D[getp(i, j)][getp(i2, j2)]= sqrt((i2 - i) * (i2 - i) + (j2 - j) * (j2 - j));
				}
			}
		}
	}
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) {
			for(int l= 0; l < 4; l++) {
				int nx= i + moves[l][0], ny= j + moves[l][1];
				if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
				edg[getp(i, j)].push_back(EDGE{getp(nx, ny), str[nx][ny] == '1'});
			}
		}
	}
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) {
			SPFA(i, j);
		}
	}
	printf("%.6lf\n", ans);
	return 0;
}