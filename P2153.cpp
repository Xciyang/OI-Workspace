#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
#define S 0
#define T 401
#define INF 0x3f3f3f3f
using namespace std;
int m, n, tmpx, tmpy, tmpz;
struct EDGE {
	int to, w, dis;
	EDGE *fedg;
};
vector< EDGE * > edg[405];
void add(int x, int y, int w, int dis) {
	EDGE *ea = new EDGE(), *eb = new EDGE();
	ea->to = y, ea->dis = dis, ea->w = w, ea->fedg = eb;
	eb->to = x, eb->dis = -dis, eb->w = 0, eb->fedg = ea;
	edg[x].push_back(ea), edg[y].push_back(eb);
	return;
}

int wp[405], w[405], dis[405];
EDGE *pre[405];
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
int toID(int x, int y) {
	return x * 2 - y;
}
int main() {
	cin >> n >> m;
	add(S, toID(1, 0), INF, 0);
	add(toID(1, 0), toID(1, 1), INF, 0);
	add(toID(n, 0), toID(n, 1), INF, 0);
	add(toID(n, 1), T, INF, 0);
	for(int i = 2; i <= n - 1; i++) add(toID(i, 0), toID(i, 1), 1, 0);
	for(int i = 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		add(toID(tmpx, 1), toID(tmpy, 0), 1, tmpz);
	}
	auto res = maxflow_cost(mindis);
	cout << res.first << ' ' << res.second << endl;
	return 0;
}