#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
#define S 0
#define T 201
#define INF 0x3f3f3f3f
using namespace std;
int n, a[101][101];
struct EDGE {
	int to, dis, w;
	EDGE *fedg;
};
vector< EDGE * > edg[205];
void add(int x, int y, int w, int dis) {
	EDGE *ea = new EDGE(), *eb = new EDGE();
	ea->to = y, ea->dis = dis, ea->w = w, ea->fedg = eb;
	eb->to = x, eb->dis = -dis, eb->w = 0, eb->fedg = ea;
	edg[x].push_back(ea), edg[y].push_back(eb);
	return;
}
int dis[205], wp[205], w[205];
EDGE *pre[205];
int SPFA() {
	for(int i = S; i <= T; i++) w[i] = dis[i] = INF, pre[i] = 0;
	queue< int > qu;
	qu.push(S);
	dis[S] = 0, wp[S] = 1;
	register int nown, to;
	while(!qu.empty()) {
		nown = qu.front(), qu.pop(), wp[nown] = 0;
		for(int i = 0; i < edg[nown].size(); i++) {
			to = edg[nown][i]->to;
			if(dis[to] > dis[nown] + edg[nown][i]->dis && edg[nown][i]->w) {
				dis[to] = dis[nown] + edg[nown][i]->dis;
				pre[to] = edg[nown][i];
				w[to] = min(w[nown], edg[nown][i]->w);
				if(!wp[to]) {
					wp[to] = 1;
					qu.push(to);
				}
			}
		}
	}
	return dis[T] != INF;
}
int mincost() {
	int res = 0, nown;
	while(SPFA()) {
		nown = T;
		while(pre[nown]) {
			pre[nown]->w -= w[T];
			pre[nown]->fedg->w += w[T];
			nown = pre[nown]->fedg->to;
		}
		res += w[T] * dis[T];
	}
	return res;
}
int SPFA2() {
	for(int i = S; i <= T; i++) w[i] = INF, dis[i] = -INF, pre[i] = 0;
	queue< int > qu;
	qu.push(S);
	dis[S] = 0, wp[S] = 1;
	register int nown, to;
	while(!qu.empty()) {
		nown = qu.front(), qu.pop(), wp[nown] = 0;
		for(int i = 0; i < edg[nown].size(); i++) {
			to = edg[nown][i]->to;
			if(dis[to] < dis[nown] + edg[nown][i]->dis && edg[nown][i]->w) {
				dis[to] = dis[nown] + edg[nown][i]->dis;
				pre[to] = edg[nown][i];
				w[to] = min(w[nown], edg[nown][i]->w);
				if(!wp[to]) {
					wp[to] = 1;
					qu.push(to);
				}
			}
		}
	}
	return dis[T] != -INF;
}
int maxcost() {
	int res = 0, nown;
	while(SPFA2()) {
		nown = T;
		while(pre[nown]) {
			pre[nown]->w -= w[T];
			pre[nown]->fedg->w += w[T];
			nown = pre[nown]->fedg->to;
		}
		res += w[T] * dis[T];
	}
	return res;
}
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		add(S, i, 1, 0);
		add(n + i, T, 1, 0);
		for(int j = 1; j <= n; j++) {
			cin >> a[i][j];
			add(i, n + j, 1,  a[i][j]);
		}
	}
	cout << mincost() << endl;
	for(int i = S; i <= T; i++) edg[i].clear();
	for(int i = 1; i <= n; i++) {
		add(S, i, 1, 0);
		add(n + i, T, 1, 0);
		for(int j = 1; j <= n; j++) {
			add(i, n + j, 1,  a[i][j]);
		}
	}
	cout << maxcost() << endl;
	return 0;
}