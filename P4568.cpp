#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
int n, m, k, tmpx, tmpy, tmpz, s, t, ans= 0x3f3f3f3f;
struct EDGE {
	int to, dis;
};
vector< EDGE > edg[10005];
int dis[10004][11], wp[10004][11];
struct NODE {
	int x, nk;
	inline int operator<(const NODE &n2) const {
		return dis[x][nk] > dis[n2.x][n2.nk];
	}
};
priority_queue< NODE > qu;
void SPFA() {
	memset(dis, 0x3f, sizeof(dis));
	dis[s][0]= 0, qu.push(NODE{s, 0}), wp[s][0]= 1;
	register NODE nown, to;
	while(!qu.empty()) {
		nown= qu.top(), qu.pop();
		wp[nown.x][nown.nk]= 0;
		for(int i= 0; i < edg[nown.x].size(); i++) {
			to.x= edg[nown.x][i].to;
			if(nown.nk < k && dis[to.x][nown.nk + 1] > dis[nown.x][nown.nk]) {
				to.nk= nown.nk + 1, dis[to.x][to.nk]= dis[nown.x][nown.nk];
				if(!wp[to.x][to.nk]) wp[to.x][to.nk]= 1, qu.push(to);
			}
			if(dis[to.x][nown.nk] > dis[nown.x][nown.nk] + edg[nown.x][i].dis) {
				to.nk= nown.nk, dis[to.x][to.nk]= dis[nown.x][nown.nk] + edg[nown.x][i].dis;
				if(!wp[to.x][to.nk]) wp[to.x][to.nk]= 1, qu.push(to);
			}
		}
	}
	return;
}
int main() {
	scanf("%d%d%d%d%d", &n, &m, &k, &s, &t);
	for(int i= 1; i <= m; i++) {
		scanf("%d%d%d", &tmpx, &tmpy, &tmpz);
		edg[tmpx].push_back(EDGE{tmpy, tmpz});
		edg[tmpy].push_back(EDGE{tmpx, tmpz});
	}
	SPFA();
	for(int i= 0; i <= k; i++) ans= min(ans, dis[t][i]);
	printf("%d\n", ans);
	return 0;
}