#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
int S;
int T;
#define INF 0X3f3f3f3f
int n, k;
char ch[2005][11][11];
long long ans;
struct EDGE {
	int to, w;
	EDGE *fedg;
};
vector< EDGE * > edg[4005];
void add(int x, int y, int w) {
	EDGE *ea = new EDGE(), *eb = new EDGE();
	ea->to = y, ea->w = w, ea->fedg = eb;
	eb->to = x, eb->w = 0, eb->fedg = ea;
	edg[x].push_back(ea), edg[y].push_back(eb);
	return;
}
int dis[4005], nxt[4005];
int bfs() {
	for(int i = S; i <= T; i++) dis[i] = INF;
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
int toID(int x, int y, int z) {
	return (x - 1) * k + y + z * n * k;
}
void clear() {
	for(int i = S; i <= T; i++) edg[i].clear();
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= k; j++) {
			add(toID(i, j, 0), toID(i, j, 1), 1);
			if(i != n)
				for(int l = 1; l <= k; l++)
					if(ch[i][j][l] == '1') add(toID(i, j, 1), toID(i + 1, l, 0), INF);
		}
	}
	return;
}
int main() {
	cin >> n >> k;
	for(int i = 1; i < n; i++) {
		for(int j = 1; j <= k; j++) {
			for(int l = 1; l <= k; l++) {
				cin >> ch[i][j][l];
			}
		}
	}
	S = 0, T = toID(n + 1, 1, 1);
	for(int i = 1; i < n; i++) {
		for(int j = i + 1; j <= n; j++) {
			clear();
			for(int l = 1; l <= k; l++) add(S, toID(i, l, 0), INF);
			for(int l = 1; l <= k; l++) add(toID(j, l, 1), T, INF);
			ans += maxflow();
		}
	}
	cout << ans << endl;
	return 0;
}