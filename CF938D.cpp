#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
using namespace std;
struct EDGE {
	int to;
	long long dis;
};
vector< EDGE > edg[200005];
int n, m, tmpx, tmpy, wp[200005];
long long tmpz, dis[200005];
struct CMP {
	inline int operator()(const int &x, const int &y) const {
		return dis[x] > dis[y];
	}
};
priority_queue< int, vector< int >, CMP > qu;
void SPFA() {
	register int nown, to;
	for(int i= 1; i <= n; i++) wp[i]= 1, qu.push(i);
	while(!qu.empty()) {
		nown= qu.top(), qu.pop(), wp[nown]= 0;
		for(int i= 0; i < edg[nown].size(); i++) {
			to= edg[nown][i].to;
			if(dis[to] > dis[nown] + edg[nown][i].dis) {
				dis[to]= dis[nown] + edg[nown][i].dis;
				if(!wp[to]) wp[to]= 1, qu.push(to);
			}
		}
	}
	return;
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		edg[tmpx].push_back(EDGE{tmpy, tmpz << 1}), edg[tmpy].push_back(EDGE{tmpx, tmpz << 1});
	}
	for(int i= 1; i <= n; i++) cin >> dis[i];
	SPFA();
	for(int i= 1; i <= n; i++) cout << dis[i] << ' ';
	putchar('\n');
	return 0;
}