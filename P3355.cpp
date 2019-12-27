#pragma GCC optimize(1)
#pragma G++ optimize(1)
#pragma GCC optimize(2)
#pragma G++ optimize(2)
#pragma GCC optimize(3)
#pragma G++ optimize(3)
#pragma GCC optimize(4)
#pragma G++ optimize(4)
#pragma GCC optimize(5)
#pragma G++ optimize(5)
#pragma GCC optimize(6)
#pragma G++ optimize(6)
#pragma GCC optimize(7)
#pragma G++ optimize(7)
#pragma GCC optimize(8)
#pragma G++ optimize(8)
#pragma GCC optimize(9)
#pragma G++ optimize(9)
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
#define S 0
#define T 40001
#define INF 0X3F3F3F3F
using namespace std;
int n, m, tmpx, tmpy, f[205][205];
struct EDGE {
	int to, w;
	EDGE *fedg;
};
inline int toid(int x, int y) {
	return (x - 1) * n + y;
}
vector< EDGE * > edg[40005];
void add(int x, int y, int w) {
	EDGE *ea = new EDGE(), *eb = new EDGE();
	ea->to = y, ea->w = w, ea->fedg = eb;
	eb->to = x, eb->w = 0, eb->fedg = ea;
	edg[x].push_back(ea), edg[y].push_back(eb);
	return;
}
int dis[40005];
int bfs() {
	for(register int i = S; i <= T; i++) dis[i] = INF;
	queue< int > qu;
	qu.push(S), dis[S] = 0;
	register int nown, to;
	while(!qu.empty()) {
		nown = qu.front(), qu.pop();
		for(register int i = 0; i < edg[nown].size(); i++) {
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
	int res = 0;
	for(register int i = 0, to; i < edg[nown].size(); i++) {
		to = edg[nown][i]->to;
		if(res == maxf) break;
		if(dis[to] == dis[nown] + 1 && edg[nown][i]->w) {
			if(int f = dfs(to, min(maxf, edg[nown][i]->w))) {
				edg[nown][i]->w -= f;
				edg[nown][i]->fedg->w += f;
				res += f;
			}
		}
	}
	if(!res) dis[nown] = 0;
	return res;
}
int maxflow() {
	int res = 0;
	while(bfs())
		while(int res2 = dfs(S, INF)) res += res2;
	return res;
}
int moves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		scanf("%d%d", &tmpx, &tmpy);
		f[tmpx][tmpy] = 1;
	}
	for(register int i = 1; i <= n; i++) {
		for(register int j = 1; j <= n; j++) {
			if(f[i][j]) continue;
			if((i + j) & 1) {
				add(S, toid(i, j), 1);
				for(register int k = 0, x, y; k < 8; k++) {
					x = i + moves[k][0], y = j + moves[k][1];
					if(x < 1 || x > n || y < 1 || y > n || f[x][y]) continue;
					add(toid(i, j), toid(x, y), INF);
				}
			}
			else {
				add(toid(i, j), T, 1);
			}
		}
	}
	printf("%d\n", n * n - m - maxflow());
	return 0;
}