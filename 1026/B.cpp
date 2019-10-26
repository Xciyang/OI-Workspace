#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int n, q, tmpx, tmpy, tmpz;
struct EDGE {
	int to, dis;
};
vector< EDGE > edg[500005];
int dep[500005], cdep[500005], f[500005][23], depp[500005];
int depx[500005], cdepx[500005];
void dfs(int nown) {
	depp[nown]= depp[f[nown][0]] + 1;
	for(int i= 1; i < 23; i++) f[nown][i]= f[f[nown][i - 1]][i - 1];
	for(int i= 0, to; i < edg[nown].size(); i++) {
		to= edg[nown][i].to;
		if(to == f[nown][0]) continue;
		f[to][0]= nown, dfs(to);
		if(dep[to] + edg[nown][i].dis > dep[nown]) {
			cdepx[nown]= depx[nown], depx[nown]= depx[to];
			cdep[nown]= dep[nown], dep[nown]= dep[to] + edg[nown][i].dis;
		}
		else if(dep[to] + edg[nown][i].dis > cdep[nown]) {
			cdepx[nown]= to;
			cdep[nown]= dep[to] + edg[nown][i].dis;
		}
	}
	return;
}
int isf(int x, int y) {
	if(x == y) return 1;
	if(dep[x] < dep[y]) swap(x, y);
	for(int i= 22; i >= 0; i--)
		if(dep[f[x][i]] > dep[y]) x= f[x][i];
	return f[x][0] == y;
}
int getf(int x, int y) {
	for(int i= 22; i >= 0; i--)
		if(dep[f[x][i]] < dep[y]) x= f[x][i];

	if(f[x][0] == y) return y;
}
int main() {
	scanf("%d%d", &n, &q);
	for(int i= 1; i < n; i++) {
		scanf("%d%d%d", &tmpx, &tmpy, &tmpz);
		edg[tmpx].push_back(EDGE{tmpy, tmpz}), edg[tmpy].push_back(EDGE{tmpx, tmpz});
	}
	for(int i= 1; i <= q; i++) {
		cin >> tmpx >> tmpy;
	}
	return 0;
}