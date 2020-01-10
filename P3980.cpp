#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
int S = 0, T = 2001;
#define INF 0x3f3f3f3f
using namespace std;
struct EDGE {
	int to, w, dis;
	EDGE *fedg;
};
vector< EDGE * > edg[2005];
void add(int x, int y, int w, int dis, int fw = 0) {
	EDGE *ea = new EDGE(), *eb = new EDGE();
	ea->to = y, ea->dis = dis, ea->w = w, ea->fedg = eb;
	eb->to = x, eb->dis = -dis, eb->w = fw, eb->fedg = ea;
	edg[x].push_back(ea), edg[y].push_back(eb);
	return;
}
int wp[2005], w[2005], dis[2005];
EDGE *pre[2005];
int mindis() {
	for(int i = S; i <= T; i++) w[i] = dis[i] = INF, pre[i] = 0;
	queue< int > qu;
	qu.push(S), dis[S] = 0, wp[S] = 1;
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
/**
 * First : flow , Second : cost
 */
pair< int, int > maxflow_cost(int (*func)()) {
	int nown, res = 0, res2 = 0;
	while(func()) {
		nown = T;
		while(pre[nown]) {
			pre[nown]->w -= w[T];
			pre[nown]->fedg->w += w[T];
			nown = pre[nown]->fedg->to;
		}
		res += w[T] * dis[T];
		res2 += w[T];
	}
	return pair< int, int >(res2, res);
}
int n, m, tmpx, tmpy, tmpz;
int main() {
	cin >> n >> m;
	add(S, 1, INF, 0);
	for(int i = 1; i <= n; i++) {
		cin >> tmpx;
		add(i, i + 1, INF - tmpx, 0);
	}
	for(int j = 1; j <= m; j++) {
		cin >> tmpx >> tmpy >> tmpz;
		add(tmpx, tmpy + 1, INF, tmpz);
	}
	add(n + 1, T, INF, 0);
	cout << maxflow_cost(mindis).second << endl;
	return 0;
}