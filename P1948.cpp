#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
int n, p, k, dis[1005][1005], tmpx, tmpy, tmpz, wp[1005][1005], ans= 0x7f7f7f7f;
struct EDG {
	int to, dis;
};
vector< EDG > edg[1005];
struct NODE {
	int x, y;
	inline bool operator<(const NODE &n2) const {
		return dis[x][y] > dis[n2.x][n2.y];
	}
};
priority_queue< NODE > qu;
int main() {
	cin >> n >> p >> k;
	for(int i= 1; i <= p; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		edg[tmpx].push_back(EDG{tmpy, tmpz});
		edg[tmpy].push_back(EDG{tmpx, tmpz});
	}
	memset(dis, 0x7f, sizeof(dis)), wp[1][0]= 1, dis[1][0]= 0;
	qu.push(NODE{1, 0});
	register NODE nown, to;
	while(!qu.empty()) {
		nown= qu.top(), qu.pop();
		wp[nown.x][nown.y]= 0;
		for(int i= 0; i < edg[nown.x].size(); i++) {
			to.x= edg[nown.x][i].to;
			if(max(dis[nown.x][nown.y], edg[nown.x][i].dis) < dis[to.x][nown.y]) {
				to.y= nown.y, dis[to.x][to.y]= max(dis[nown.x][nown.y], edg[nown.x][i].dis);
				if(!wp[to.x][to.y]) wp[to.x][to.y]= 1, qu.push(to);
			}
			if(nown.y < k && dis[nown.x][nown.y] < dis[to.x][nown.y + 1]) {
				to.y= nown.y + 1, dis[to.x][to.y]= dis[nown.x][nown.y];
				if(!wp[to.x][to.y]) wp[to.x][to.y]= 1, qu.push(to);
			}
		}
	}
	for(int i= 1; i <= k; i++) ans= min(ans, dis[n][i]);
	if(ans == 0x7f7f7f7f)
		cout << -1 << endl;
	else
		cout << ans << endl;
	return 0;
}