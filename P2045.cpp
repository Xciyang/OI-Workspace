#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
#define S 0
#define T 5001
#define INF 0x3f3f3f3f
using namespace std;
int n, k, r[5005], a[55][55];
struct EDGE {
	int to, w, dis;
	EDGE *fedg;
};
vector< EDGE * > edg[5005];
void add(int x, int y, int w, int dis) {
	EDGE *ea = new EDGE(), *eb = new EDGE();
	ea->to = y, ea->dis = dis, ea->w = w, ea->fedg = eb;
	eb->to = x, eb->dis = -dis, eb->w = 0, eb->fedg = ea;
	edg[x].push_back(ea), edg[y].push_back(eb);
	return;
}
int wp[5005], w[5005], dis[5005];
EDGE *pre[5005];
int SPFA() {
	for(int i = S; i <= T; i++) w[i] = INF, dis[i] = -INF, pre[i] = 0;
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
	return dis[T] != -INF;
}
int maxcost() {
	int nown, res = 0;
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
inline int toID(int x, int y, int c) {
	return ((x - 1) * n + y) + c * n * n;
}
int main() {
	cin >> n >> k;
	add(S, toID(1, 1, 0), k, 0);
	add(toID(n, n, 1), T, k, 0);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> a[i][j];
			add(toID(i, j, 0), toID(i, j, 1), 1, a[i][j]);
			add(toID(i, j, 0), toID(i, j, 1), INF, 0);
			if(i != n) add(toID(i, j, 1), toID(i + 1, j, 0), INF, 0);
			if(j != n) add(toID(i, j, 1), toID(i, j + 1, 0), INF, 0);
		}
	}
    cout << maxcost() << endl;
	return 0;
}