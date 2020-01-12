#include <iostream>
#include <stdio.h>
using namespace std;
#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
int S = 0, T = 601;
#define INF 0x3f3f3f3f
using namespace std;
struct EDGE {
	int to, w, dis;
	EDGE *fedg;
};
vector< EDGE * > edg[605];
void add(int x, int y, int w, int dis, int fw = 0) {
	EDGE *ea = new EDGE(), *eb = new EDGE();
	ea->to = y, ea->dis = dis, ea->w = w, ea->fedg = eb;
	eb->to = x, eb->dis = -dis, eb->w = fw, eb->fedg = ea;
	edg[x].push_back(ea), edg[y].push_back(eb);
	return;
}
int wp[605], w[605], dis[605];
EDGE *pre[605];
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
int n, m, tmpx, tmpy, tmpz, a[10][61];
int main() {
	cin >> m >> n;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> a[j][i];
		}
	}
	for(int i = 1; i <= n; i++) add(S, i, 1, 0);
	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) {
			add(i * n + j, T, 1, 0);
			for(int k = 1; k <= n; k++) {
				add(k, i * n + j, INF, a[i][k] * j);
			}
		}
	}
	printf("%.2lf\n", (double)maxflow_cost(mindis).second / n);
	return 0;
}