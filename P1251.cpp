#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
#define S 0
#define T 4001
#define INF 100000000
#define DISINF 0x3f3f3f3f3f3f3f
using namespace std;
int N, p, m, f, n, s, r[4005];
struct EDGE {
	int to, w;
	long long dis;
	EDGE *fedg;
};
vector< EDGE * > edg[4005];
void add(int x, int y, int w, int dis) {
	EDGE *ea = new EDGE(), *eb = new EDGE();
	ea->to = y, ea->dis = dis, ea->w = w, ea->fedg = eb;
	eb->to = x, eb->dis = -dis, eb->w = 0, eb->fedg = ea;
	edg[x].push_back(ea), edg[y].push_back(eb);
	return;
}
long long dis[4005];
int wp[4005], w[4005];
EDGE *pre[4005];
int SPFA() {
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
long long mincost() {
	long long res = 0;
	int nown;
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
int main() {
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> r[i];
	cin >> p >> m >> f >> n >> s;
	for(int i = 1; i <= N; i++) {
		add(S, i * 2 - 1, INF, p);
		add(i * 2 - 1, T, r[i], 0);
		add(S, i * 2, r[i], 0);
		if(i + 1 <= N) add(i * 2, (i + 1) * 2, INF, 0);
		if(i + m <= N) add(i * 2, ((i + m) * 2 - 1), INF, f);
		if(i + n <= N) add(i * 2, (i + n) * 2 - 1, INF, s);
	}
	cout << mincost() << endl;
	return 0;
}