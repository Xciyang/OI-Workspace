#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
int n, m, b, maxf, f[10005], tmpx, tmpy, tmpz;
struct EDG {
	int to, dis;
};
vector< EDG > edg[10005];
int dis[10005], wp[10005];
queue< int > qu;
int SPFA(int x) {
	if(f[1] > x) return 0;
	memset(dis, 0x3f, sizeof(dis));
	dis[1]= 0, qu.push(1), wp[1]= 1;
	register int nown, to;
	while(!qu.empty()) {
		nown= qu.front(), qu.pop(), wp[nown]= 0;
		for(int i= 0; i < edg[nown].size(); i++) {
			to= edg[nown][i].to;
			if(f[to] > x) continue;
			if(dis[to] > dis[nown] + edg[nown][i].dis) {
				dis[to]= dis[nown] + edg[nown][i].dis;
				if(!wp[to]) wp[to]= 1, qu.push(to);
			}
		}
	}
	return dis[n] < b;
}
int main() {
	cin >> n >> m >> b;
	for(int i= 1; i <= n; i++) cin >> f[i], maxf= max(maxf, f[i]);
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		edg[tmpx].push_back(EDG{tmpy, tmpz}), edg[tmpy].push_back(EDG{tmpx, tmpz});
	}
	int l= 0, r= maxf, mid, ans= -1;
	while(l <= r) {
		mid= (l + r) >> 1;
		if(SPFA(mid))
			r= mid - 1, ans= mid;
		else
			l= mid + 1;
	}
	if(ans == -1)
		cout << "AFK" << endl;
	else
		cout << ans << endl;
	return 0;
}