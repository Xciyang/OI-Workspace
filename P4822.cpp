#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
using namespace std;
int n, m, k, tmpx, tmpy, tmpz, f[55][55], wp[55][55], ans= 0x3f3f3f3f;
struct EDGE {
	int to, dis;
};
vector< EDGE > edg[55];
struct NODE {
	int x, y;
	inline int operator<(const NODE &n2) const {
		return f[x][y] > f[n2.x][n2.y];
	}
};
priority_queue< NODE > qu;
void SPFA() {
	memset(f, 0x3f, sizeof(f)), f[1][0]= 0;
	qu.push(NODE{1, 0}), wp[1][0]= 1;
	register NODE nown, to;
	while(!qu.empty()) {
		nown= qu.top(), qu.pop(), wp[nown.x][nown.y]= 0;
		for(int i= 0; i < (int)edg[nown.x].size(); i++) {
			to.x= edg[nown.x][i].to;
			if(f[to.x][nown.y] > f[nown.x][nown.y] + edg[nown.x][i].dis) {
				to.y= nown.y, f[to.x][to.y]= f[nown.x][nown.y] + edg[nown.x][i].dis;
				if(!wp[to.x][to.y]) wp[to.x][to.y]= 1, qu.push(to);
			}
			if(nown.y + 1 <= k && f[to.x][nown.y + 1] > f[nown.x][nown.y] + edg[nown.x][i].dis / 2) {
				to.y= nown.y + 1, f[to.x][to.y]= f[nown.x][nown.y] + edg[nown.x][i].dis / 2;
				if(!wp[to.x][to.y]) wp[to.x][to.y]= 1, qu.push(to);
			}
		}
	}
	return;
}
int main() {
	cin >> n >> m >> k;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		edg[tmpx].push_back(EDGE{tmpy, tmpz}), edg[tmpy].push_back(EDGE{tmpx, tmpz});
	}
	SPFA();
	for(int i= 0; i <= k; i++) ans= min(ans, f[n][i]);
	cout << ans << endl;
	return 0;
}