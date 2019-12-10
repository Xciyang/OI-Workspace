#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
using namespace std;
#define S 0
#define T 430
#define INF 0x3f3f3f3f
int m, n, c[275], r[155], sum;
struct EDGE {
	int to, w;
	EDGE *fedg;
};
vector< EDGE * > edg[431];
void add(int x, int y, int w) {
	EDGE *e1 = new EDGE(), *e2 = new EDGE();
	e1->to = y, e1->w = w, e1->fedg = e2;
	e2->to = x, e2->w = 0, e2->fedg = e1;
	edg[x].push_back(e1), edg[y].push_back(e2);
	return;
}
int dis[431];
int bfs() {
	memset(dis, 0x3f, sizeof(dis));
	register int nown, to;
	queue< int > qu;
	qu.push(S), dis[S] = 0;
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
    register int to;
	for(int i = 0; i < edg[nown].size(); i++) {
        to = edg[nown][i]->to;
		if(edg[nown][i]->w && dis[to] == dis[nown] + 1) {
			int f = dfs(to, min(maxf, edg[nown][i]->w));
			if(f) {
				edg[nown][i]->w -= f;
				edg[nown][i]->fedg->w += f;
				return f;
			}
		}
	}

	return 0;
}
int maxflow() {
	int res = 0, tmpx;
	while(bfs())
		while(tmpx = dfs(S, INF)) res += tmpx;
	return res;
}
int main() {
	cin >> m >> n;
	for(int i = 1; i <= m; i++) cin >> r[i], add(S, i, r[i]), sum += r[i];
	for(int i = 1; i <= n; i++) cin >> c[i], add(m + i, T, c[i]);
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= n; j++) add(i, m + j, 1);
	if(maxflow() == sum) {
		cout << 1 << endl;
		for(int i = 1; i <= m; i++) {
			for(int j = 0; j < edg[i].size(); j++) {
				if(edg[i][j]->to && !edg[i][j]->w) cout << edg[i][j]->to - m << ' ';
			}
			cout << endl;
		}
	}
	else {
		cout << 0 << endl;
	}
	return 0;
}