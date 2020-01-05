#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
int n, e, tmpx, tmpy, c, m;
vector< int > edg[1005];
int a[1005][1005], DIS[1005][1005], wp[1005];
void SPFA(int s, int *dis) {
	for(int i = 1; i <= n; i++) dis[i] = 0x7f7f7f7f, wp[i] = 0;
	dis[s] = 0, wp[s] = 1;
	queue< int > qu;
	qu.push(s);
	register int nown, to;
	while(!qu.empty()) {
		nown = qu.front(), qu.pop(), wp[nown] = 0;
		for(int i = 0; i < edg[nown].size(); i++) {
			to = edg[nown][i];
			if(dis[to] > dis[nown] + 1) {
				dis[to] = dis[nown] + 1;
				if(!wp[to]) wp[to] = 1, qu.push(to);
			}
		}
	}
	return;
}
int vs2[1005][1005];
int getnext(int nowx, int nowy) {
	if(vs2[nowx][nowy]) return vs2[nowx][nowy];
	register int to, resb = 0x3f3f3f3f, ress;
	for(int i = 0; i < edg[nowy].size(); i++) {
		to = edg[nowy][i];
		if(DIS[to][nowx] < resb || (DIS[to][nowx] == resb && to < ress)) {
			resb = DIS[to][nowx];
			ress = to;
		}
	}
	return vs2[nowx][nowy] = ress;
}
double f[1005][1005];
int vs[1005][1005];
double getf(int nowx, int nowy) {
	if(vs[nowx][nowy]) return f[nowx][nowy];
	int &lv = vs[nowx][nowy];
	double &lf = f[nowx][nowy];
	if(nowx == nowy) return lv = 1, lf = 0;
	nowy = getnext(nowx, nowy);
	if(nowx == nowy) return lv = 1, lf = 1;
	nowy = getnext(nowx, nowy);
	if(nowx == nowy) return lv = 1, lf = 1;
	double res = (getf(nowx, nowy) + 1) / (1 + edg[nowx].size());
	for(int i = 0; i < edg[nowx].size(); i++) res += (getf(edg[nowx][i], nowy) + 1) / (1 + edg[nowx].size());
	lv = 1, lf = res;
	return lf;
}
int main() {
	cin >> n >> e;
	cin >> c >> m;
	for(int i = 1; i <= e; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(tmpy);
		edg[tmpy].push_back(tmpx);
	}
	for(int i = 1; i <= n; i++) SPFA(i, DIS[i]);
	printf("%.3lf\n", getf(m, c));
	return 0;
}