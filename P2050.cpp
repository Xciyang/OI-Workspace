#include <iostream>
#include <stdio.h>
using namespace std;
#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
int S = 0, T = 4041;
#define INF 0x3f3f3f3f
using namespace std;
struct EDGE {
	int to, w, dis;
	EDGE *fedg;
};
vector< EDGE * > edg[80100];
void add(int x, int y, int w, int dis, int fw = 0) {
	EDGE *ea = new EDGE(), *eb = new EDGE();
	ea->to = y, ea->dis = dis, ea->w = w, ea->fedg = eb;
	eb->to = x, eb->dis = -dis, eb->w = fw, eb->fedg = ea;
	edg[x].push_back(ea), edg[y].push_back(eb);
	return;
}
int wp[80100], w[80100], dis[80100];
EDGE *pre[80100];
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
int n, m, tmpx, tmpy, tmpz, a[41][101], p[41], sum;

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
		int i = pre[T]->fedg->to;
		add(i + 1, T, 1, 0);
		for(int j = 1; j <= n; j++) add(sum * m + j, i + 1, 1, a[j][i / sum + 1] * (i % sum + 1));
	}
	return pair< int, int >(res2, res);
}
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> p[i], sum += p[i];
	T = sum * m + n + 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) cin >> a[i][j];
	for(int i = 1; i <= n; i++) add(S, sum * m + i, p[i], 0);
	for(int i = 1; i <= m; i++) {
		add((i - 1) * sum + 1, T, 1, 0);
		for(int j = 1; j <= n; j++) add(sum * m + j, (i - 1) * sum + 1, 1, a[j][i] * 1);
	}
	cout << maxflow_cost(mindis).second << endl;
	return 0;
}