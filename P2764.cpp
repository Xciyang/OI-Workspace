#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
#define S 0
#define T 400
#define INF 0X3f3f3f3f
int n, m, tmpx, tmpy;
struct EDGE {
	int to, w;
	EDGE *fedg;
};
vector< EDGE * > edg[401];
void add(int x, int y, int w) {
	EDGE *ea = new EDGE(), *eb = new EDGE();
	ea->to = y, ea->w = w, ea->fedg = eb;
	eb->to = x, eb->w = 0, eb->fedg = ea;
	edg[x].push_back(ea), edg[y].push_back(eb);
	return;
}
int dis[401], nxt[401];
int bfs() {
	memset(dis, 0x3f, sizeof(dis));
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
	return dis[T] != 0x3f3f3f3f;
}
int dfs(int nown, int maxf) {
	if(nown == T) return maxf;
	register int to;
	for(int i = 0; i < edg[nown].size(); i++) {
		to = edg[nown][i]->to;
		if(edg[nown][i]->w && dis[to] == dis[nown] + 1) {
			if(int f = dfs(to, min(maxf, edg[nown][i]->w))) {
				edg[nown][i]->w -= f;
				edg[nown][i]->fedg->w += f;
				nxt[nown] = to;
				return f;
			}
		}
	}
	return 0;
}
int maxflow() {
	int res = 0;
	while(bfs()) {
		while(int tmpres = dfs(S, INF)) res += tmpres;
	}
	return res;
}
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) add(S, i, 1), add(i + n, T, 1);
	for(int i = 1; i <= m; i++) {
		cin >> tmpx >> tmpy;
		add(tmpx, tmpy + n, 1);
	}
	int res = maxflow();
	for(int i = 1, j; i <= n; i++) {
		j = n + i;
		if(!nxt[j]) {
			do {
				cout << j - n << ' ';
				j = nxt[j - n];
			} while(j);
			cout << endl;
		}
	}
	cout << n - res << endl;
	return 0;
}