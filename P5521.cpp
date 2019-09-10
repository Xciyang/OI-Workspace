#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int n, fa[100005], w[100005], f[100005];
struct EDGE {
	int to, p;
	bool operator<(const EDGE &e) const {
		return p < e.p;
	}
};

vector< EDGE > edg[100005];
void dfs(int nowx) {
	f[nowx]= w[nowx];
	if(edg[nowx].empty()) return;
	for(int i= 0; i < edg[nowx].size(); i++) {
		dfs(edg[nowx][i].to);
		edg[nowx][i].p= w[edg[nowx][i].to] - f[edg[nowx][i].to], f[nowx]+= w[edg[nowx][i].to];
	}
	sort(edg[nowx].begin(), edg[nowx].end());
	for(int i= 0, sum= 0; i < edg[nowx].size(); i++) f[nowx]= max(f[nowx], sum + f[edg[nowx][i].to]), sum+= w[edg[nowx][i].to];
	return;
}
int main() {
	cin >> n;
	for(int i= 2; i <= n; i++) {
		cin >> fa[i];
		edg[fa[i]].push_back(EDGE{i, 0});
	}
	for(int i= 1; i <= n; i++) cin >> w[i];
	dfs(1);
	for(int i= 1; i <= n; i++) cout << f[i] << ' ';
	return 0;
}