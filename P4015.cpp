#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
#define S 0
#define T 201
#define INF 100000000
#define DISINF 0x3f3f3f3f3f3f3f
using namespace std;
int m, n, tmpx;
struct EDGE {
	int to, w, lw;
	long long dis;
	EDGE *fedg;
};
vector< EDGE * > edg[205];
void add(int x, int y, int w, int dis) {
	EDGE *ea = new EDGE(), *eb = new EDGE();
	ea->to = y, ea->dis = dis, ea->w = ea->lw = w, ea->fedg = eb;
	eb->to = x, eb->dis = -dis, eb->w = eb->lw = 0, eb->fedg = ea;
	edg[x].push_back(ea), edg[y].push_back(eb);
	return;
}
void undoedg() {
	for(int i = S; i <= T; i++) {
		for(int j = 0; j < edg[i].size(); j++) {
			edg[i][j]->w = edg[i][j]->lw;
		}
	}
	return;
}
long long dis[205];
int wp[205], w[205];
EDGE *pre[205];
int mindis() {
	for(int i = S; i <= T; i++) w[i] = INF, dis[i] = DISINF, pre[i] = 0;
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
	return dis[T] != DISINF;
}
int maxdis() {
	for(int i = S; i <= T; i++) w[i] = INF, dis[i] = -DISINF, pre[i] = 0;
	queue< int > qu;
	qu.push(S), dis[S] = 0, wp[S] = 1;
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
	return dis[T] != -DISINF;
}
long long mcost(int (*func)()) {
	long long res = 0;
	int nown;
	while(func()) {
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
	cin >> m >> n;
	for(int i = 1; i <= m; i++) {
		cin >> tmpx;
		add(S, i, tmpx, 0);
	}
	for(int i = 1; i <= n; i++) {
		cin >> tmpx;
		add(m + i, T, tmpx, 0);
	}
	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> tmpx;
			add(i, m + j, INF, tmpx);
		}
	}
	cout << mcost(mindis) << endl;
	undoedg();
	cout << mcost(maxdis) << endl;
	return 0;
}