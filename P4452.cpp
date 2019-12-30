#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
#define S 0
#define S2 401
#define T 402
#define INF 1e9
using namespace std;
int n, m, k, tt, t[205][205], f[205][205];
struct EDGE {
	int to, dis, w;
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
int dis[405], wp[405], w[405];
EDGE *pre[405];
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
struct NODE {
	int a, b, s, t, c;
} a[205];
int main() {
	cin >> n >> m >> k >> tt;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> t[i][j];
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> f[i][j];
		}
	}
	for(int i = 1; i <= m; i++) {
		cin >> a[i].a >> a[i].b >> a[i].s >> a[i].t >> a[i].c;
		++a[i].a, ++a[i].b;
	}
	add(S, S2, k, 0);
	for(int i = 1; i <= m; i++) {
		add(i * 2 - 1, i * 2, 1, a[i].c);
		if(a[i].s >= t[1][a[i].a]) {
			add(S2, i * 2 - 1, 1, -f[1][a[i].a]);
		}
		if(a[i].t + t[a[i].b][1] <= tt) {
			add(i * 2, T, 1, -f[a[i].b][1]);
		}
		for(int j = 1; j <= m; j++) {
			if(a[i].t + t[a[i].b][a[j].a] <= a[j].s) {
				add(i * 2, j * 2 - 1, 1, -f[a[i].b][a[j].a]);
			}
		}
	}
	cout << maxcost() << endl;
	return 0;
}