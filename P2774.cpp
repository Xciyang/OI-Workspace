#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
#define S 0
#define T 10004
#define INF 0X7F7F7F7F
int n, m, tmpx, sum;
int moves[][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
struct EDGE {
	int to, w;
	EDGE *fedg;
};
vector< EDGE * > edg[10005];
inline int praseID(int x, int y) {
	return (x - 1) * m + y;
}
void add(int x, int y, int w) {
	EDGE *ea = new EDGE(), *eb = new EDGE();
	ea->to = y, ea->w = w, ea->fedg = eb;
	eb->to = x, eb->w = 0, eb->fedg = ea;
	edg[x].push_back(ea), edg[y].push_back(eb);
	return;
}
int dis[10005];
int bfs() {
	for(int i = 0; i <= T; i++) dis[i] = INF;
	queue< int > qu;
	dis[S] = 0, qu.push(S);
	register int nown, to;
	while(!qu.empty()) {
		nown = qu.front(), qu.pop();
		for(int i = 0; i < edg[nown].size(); i++) {
			to = edg[nown][i]->to;
			if(dis[to] > dis[nown] + 1 && edg[nown][i]->w) {
				dis[to] = dis[nown] + 1;
				qu.push(to);
			}
		}
	}
	return dis[T] != INF;
}
int dfs(int nown, int maxf) {
	if(nown == T) return maxf;
	register int to;
	for(int i = 0; i < edg[nown].size(); i++) {
		to = edg[nown][i]->to;
		if(dis[to] == dis[nown] + 1 && edg[nown][i]->w) {
			if(int f = dfs(to, min(maxf, edg[nown][i]->w))) {
				edg[nown][i]->w -= f;
				edg[nown][i]->fedg->w += f;
				return f;
			}
		}
	}
	return 0;
}
int maxflow() {
	int res = 0;
	while(bfs())
		while(int res2 = dfs(S, INF)) res += res2;
	return res;
}
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> tmpx;
			sum += tmpx;
			if((i + j) & 1) {
				add(S, praseID(i, j), tmpx);
			}
			else {
				add(praseID(i, j), T, tmpx);
			}
		}
	}
	for(int i = 1, x; i <= n; i++) {
		for(int j = 1, y; j <= m; j++) {
			if((i + j) & 1) {
				for(int k = 0; k < 4; k++) {
					x = i + moves[k][0], y = j + moves[k][1];
					if(x < 1 || x > n || y < 1 || y > m) continue;
					add(praseID(i, j), praseID(x, y), INF);
				}
			}
		}
	}
	cout << sum - maxflow() << endl;
	return 0;
}