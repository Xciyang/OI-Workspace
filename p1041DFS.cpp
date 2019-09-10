#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int n, p, head[301], edptr= 1;
int tmpx, tmpy;
struct edge {
	int to, nexty;
} eds[1001];
void add(int a, int b) {
	eds[edptr].to= b, eds[edptr].nexty= head[a];
	head[a]= edptr++;
	return;
}
int dep[301], f[301], cutd[301];
vector< int > node[302];
void cut(int nown, int s) {
	cutd[nown]= s;
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to != f[nown]) cut(to, s);
	}
	return;
}
void dfs1(int nown, int fa) {
	dep[nown]= dep[fa] + 1, f[nown]= fa;
	node[dep[nown]].push_back(nown);
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to != fa) dfs1(to, nown);
	}
	return;
}
int ans= 0x3f3f3f3f;
void dfs2(int deep, int cost) {
	if(cost >= ans) return;
	int notsolve= 0;
	for(int i= 0; i < (int)node[deep].size(); i++)
		if(!cutd[node[deep][i]]) ++notsolve;
	if(!notsolve) {
		ans= cost;
		return;
	}
	for(int i= 0; i < (int)node[deep].size(); i++) {
		if(cutd[node[deep][i]]) continue;
		cut(node[deep][i], 1);
		dfs2(deep + 1, cost + notsolve - 1);
		cut(node[deep][i], 0);
	}
	return;
}
int main() {
	cin >> n >> p;
	for(int i= 0; i < p; i++) {
		cin >> tmpx >> tmpy;
		add(tmpx, tmpy), add(tmpy, tmpx);
	}
	dfs1(1, 0), dfs2(2, 1);
	cout << ans << endl;
	return 0;
}
/*
8 7
1 2
1 3
1 4
2 5
2 6
3 7
4 8

*/