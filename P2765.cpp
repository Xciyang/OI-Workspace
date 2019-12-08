#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
#include <math.h>
using namespace std;
#define S 0
#define T 1
#define INF 0x3f3f3f3f
int n;
struct EDGE {
	int to, w;
	EDGE *fedg;
};
vector< EDGE * > edge[5000];
inline void add(int a, int b, int c) {
	EDGE *ea= new EDGE(), *eb= new EDGE();
	ea->to= b, ea->w= c, ea->fedg= eb;
	eb->to= a, eb->w= 0, eb->fedg= ea;
	edge[a].push_back(ea), edge[b].push_back(eb);
	return;
}
int nptr, nowp, dis[5000];
int bfs() {
	memset(dis, 0x3f, sizeof(dis));
	queue< int > qu;
	dis[S]= 0;
	qu.push(S);
	register int nown, to;
	while(!qu.empty()) {
		nown= qu.front(), qu.pop();
		for(int i= 0; i < edge[nown].size(); i++) {
			to= edge[nown][i]->to;
			if(dis[to] > dis[nown] + 1 && edge[nown][i]->w) {
				dis[to]= dis[nown] + 1;
				qu.push(to);
			}
		}
	}
	return dis[T] != INF;
}
int head[60], pre[5000];
int dfs(int nown, int maxf) {
	if(nown == T) return maxf;
	register int to;
	for(int i= 0; i < edge[nown].size(); i++) {
		to= edge[nown][i]->to;
		if(dis[to] == dis[nown] + 1 && edge[nown][i]->w > 0) {
			int tf= dfs(to, min(maxf, edge[nown][i]->w));
			if(tf) {
				pre[to >> 1]= nown >> 1;
				edge[nown][i]->w-= tf;
				edge[nown][i]->fedg->w+= tf;
				return tf;
			}
		}
	}
	return 0;
}
int maxflow() {
	int res= 0, nowx;
	while(bfs())
		while(nowx= dfs(S, INF)) res+= nowx;
	return res;
}
int main() {
	cin >> n;
	while(nptr <= n) {
		++nowp;
		add(S, nowp << 1, 1);
		add(nowp << 1 | 1, T, 1);
		for(int i= (int)sqrt(nowp) + 1; i * i - nowp < nowp; i++) add(nowp << 1, (i * i - nowp) << 1 | 1, 1);
		int res= maxflow();
		if(!res) head[++nptr]= nowp;
	}
	cout << nowp - 1 << endl;
	for(int i= 1; i <= n; i++) {
		for(int j= head[i]; j; j= pre[j]) cout << j << ' ';
		cout << endl;
	}
	return 0;
}