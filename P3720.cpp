#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
int n, m;
struct EDGE {
	int y, p, q;
};
vector< EDGE > edg[100005];
vector< EDGE > fedg[100005];

int tmpx, tmpy, tmpz, tmpk;
inline int getp(const EDGE &e) {
	return e.p;
}
inline int getq(const EDGE &e) {
	return e.q;
}
int dis1[100005], dis2[100005], wp[100005];
typedef int (*FUNCTIONGETDIS)(const EDGE &e);
void SPFA(int *dis, const FUNCTIONGETDIS &f) {
	for(int i= 1; i <= n; i++) dis[i]= 0x3f3f3f3f, wp[i]= 0;
	queue< int > qu;
	qu.push(n), wp[n]= 1, dis[n]= 0;
	register int nown, to, disl;
	while(!qu.empty()) {
		nown= qu.front(), qu.pop();
		wp[nown]= 0;
		for(int i= 0; i < fedg[nown].size(); i++) {
			to= fedg[nown][i].y, disl= f(fedg[nown][i]);
			if(dis[to] > dis[nown] + disl) {
				dis[to]= dis[nown] + disl;
				if(!wp[to]) wp[to]= 1, qu.push(to);
			}
		}
	}
	return;
}
int ans[100005];
void SPFA2() {
	for(int i= 1; i <= n; i++) ans[i]= 0x3f3f3f3f, wp[i]= 0;
	queue< int > qu;
	qu.push(1), wp[1]= 1, ans[1]= 0;
	register int nown, to, r1, r2;
	while(!qu.empty()) {
		nown= qu.front(), qu.pop();
		wp[nown]= 0;
		for(int i= 0; i < edg[nown].size(); i++) {
			to= edg[nown][i].y, r1= (dis1[nown] != dis1[to] + edg[nown][i].p), r2= (dis2[nown] != dis2[to] + edg[nown][i].q);
			if(ans[to] > ans[nown] + r1 + r2) {
				ans[to]= ans[nown] + r1 + r2;
				if(!wp[to]) wp[to]= 1, qu.push(to);
			}
		}
	}
	return;
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz >> tmpk;
		edg[tmpx].push_back(EDGE{tmpy, tmpz, tmpk});
		fedg[tmpy].push_back(EDGE{tmpx, tmpz, tmpk});
	}
	SPFA(dis1, getp), SPFA(dis2, getq), SPFA2();
	cout << ans[n] << endl;
	return 0;
}