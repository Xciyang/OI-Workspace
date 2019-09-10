#include <iostream>
#include <stdio.h>
using namespace std;
#define int long long
int n, m, edptr= 1, head[200001], tmpx, tmpy, tmpz, rt1, rt2, ans;
struct edge {
	int to, nexty, dis;
} eds[500001];
void add(int a, int b, int c) {
	eds[edptr].to= b, eds[edptr].nexty= head[a], eds[edptr].dis= c;
	head[a]= edptr++;
	return;
}
int dis[2][200001];
void dfs(int id, int nown, int fa) {
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == fa) continue;
		dis[id][to]= dis[id][nown] + eds[i].dis;
		dfs(id, to, nown);
	}
	return;
}
signed main() {
	cin >> n >> m;
	for(int i= 0; i < m; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		add(tmpx, tmpy, tmpz), add(tmpy, tmpx, tmpz);
	}
	dfs(0, 1, 0);
	for(int i= 1; i <= n; i++)
		if(dis[0][i] > dis[0][rt1]) rt1= i;
	dis[0][rt1]= 0, dfs(0, rt1, 0);
	for(int i= 1; i <= n; i++)
		if(dis[0][i] > dis[0][rt2]) rt2= i;
	dfs(1, rt2, 0);
	for(int i= 1; i <= n; i++) {
		ans= max(ans, min(dis[0][i], dis[1][i]));
	}
	cout << ans + dis[0][rt2] << endl;
	return 0;
}