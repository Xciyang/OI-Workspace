#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
using namespace std;
int n, m, k, ans;
struct EDGE {
	int to;
	long long dis;
};
vector< EDGE > v[100005];
int wp[100005], wp2[100005];
long long tmpx, tmpy, tmpz, dis[100005];
queue< int > qu;
void SPFA() {
	register int nown, to;
	while(!qu.empty()) {
		nown= qu.front(), qu.pop(), wp[nown]= 0;
		for(int i= 0; i < (int)v[nown].size(); i++) {
			to= v[nown][i].to;
			if(dis[to] == dis[nown] + v[nown][i].dis) wp2[to]= 0;
			if(dis[to] > dis[nown] + v[nown][i].dis) {
				dis[to]= dis[nown] + v[nown][i].dis, wp2[to]= 0;
				if(!wp[to]) wp[to]= 1, qu.push(to);
			}
		}
	}
	return;
}
int main() {
	cin >> n >> m >> k;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		v[tmpx].push_back(EDGE{tmpy, tmpz}), v[tmpy].push_back(EDGE{tmpx, tmpz});
	}
	memset(dis, 0x3f, sizeof(dis)), dis[1]= 0;
	wp[1]= 0, qu.push(1);
	for(int i= 1; i <= k; i++) {
		cin >> tmpx >> tmpy;
		if(dis[tmpx] > tmpy) {
			if(!wp[tmpx]) wp[tmpx]= 1, qu.push(tmpx);
			dis[tmpx]= tmpy, wp2[tmpx]= 1;
		}
	}
	SPFA();
	ans= k;
	for(int i= 1; i <= n; i++) ans-= wp2[i];
	cout << ans << endl;
	return 0;
}