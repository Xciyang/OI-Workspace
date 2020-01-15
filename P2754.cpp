#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <time.h>
using namespace std;
int n, m, k, S = 0, T = 1000001, TT;
#define INF 0X7f3f3f3f
struct EDGE {
	int to, w;
	EDGE *fedg;
};
vector< EDGE * > edg[1000005];
void add(int x, int y, int w) {
	EDGE *ea = new EDGE(), *eb = new EDGE();
	ea->to = y, ea->w = w, ea->fedg = eb;
	eb->to = x, eb->w = 0, eb->fedg = ea;
	edg[x].push_back(ea), edg[y].push_back(eb);
	return;
}
int dis[1000005];
int bfs() {
	for(int i = S; i <= TT; i++) dis[i] = INF;
	dis[T] = INF;
	queue< int > qu;
	dis[S] = 0;
	qu.push(S);
	register int nown, to;
	while(!qu.empty()) {
		nown = qu.front(), qu.pop();
		for(int i = 0; i < edg[nown].size(); i++) {
			to = edg[nown][i]->to;
			if(edg[nown][i]->w && dis[to] > dis[nown] + 1) {
				dis[to] = dis[nown] + 1;
				qu.push(to);
			}
		}
	}
	return dis[T] != INF;
}
int dfs(int nown, int maxf) {
	if(nown == T) return maxf;
	register int to, res = 0;
	for(int i = 0; i < edg[nown].size(); i++) {
		to = edg[nown][i]->to;
		if(edg[nown][i]->w && dis[to] == dis[nown] + 1) {
			if(int f = dfs(to, min(maxf, edg[nown][i]->w))) {
				edg[nown][i]->w -= f;
				edg[nown][i]->fedg->w += f;
				res += f, maxf -= f;
				if(!maxf) break;
			}
		}
	}
	return res;
}
int maxflow() {
	int res = 0;
	while(bfs()) res += dfs(S, INF);
	return res;
}
int toID(int x, int t) {
	return t * (n + 2) + x + 2;
}
int p[100], h[100], r[100][100];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= m; i++) {
		scanf("%d%d", h + i, p + i);
		for(int j = 0; j < p[i]; j++) scanf("%d", r[i] + j);
	}
	int ans = 0, res = 0;
	while(res < k) {
		if(ans > 500 || (double)clock() / CLOCKS_PER_SEC > 0.5) {
			ans = 1;
			break;
		}
		add(S, toID(0, ans), INF);
		add(toID(-1, ans), T, INF);
		if(ans) {
			for(int i = -1; i <= n; i++) add(toID(i, ans - 1), toID(i, ans), INF);
			for(int i = 1; i <= m; i++) add(toID(r[i][(ans - 1) % p[i]], ans - 1), toID(r[i][ans % p[i]], ans), h[i]);
		}
		TT = toID(n, ans), res += maxflow(), ++ans;
	}
	cout << ans - 1 << endl;
	return 0;
}