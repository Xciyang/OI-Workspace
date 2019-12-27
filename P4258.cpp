#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
#define S 0
#define T 404
using namespace std;
int t, n, m, e, tmpx, tmpy;
struct EDGE {
	int to, dis, w;
	EDGE *fedg;
};
vector< EDGE * > edg[405];
void add(int x, int y, int w, int dis) {
	EDGE *ea = new EDGE(), *eb = new EDGE();
	ea->to = y, ea->dis = dis, ea->w = w, ea->fedg = eb;
	eb->to = x, eb->dis = dis, eb->w = 0, eb->fedg = ea;
	edg[x].push_back(ea), edg[y].push_back(eb);
	return;
}
int vis[305], f[305], nxt[305];
void BFS(int s) {
	queue< int > qu;
	return;
}
int main() {
	cin >> t;
	while(t--) {
		cin >> n >> m >> e;
		for(int i = 1; i <= n; i++) {
		}
	}
	return 0;
}