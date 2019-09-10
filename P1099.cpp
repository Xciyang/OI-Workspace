#include <iostream>
#include <stdio.h>
using namespace std;
int n, s, tmpx, tmpy, tmpz, head[301], edptr= 1, ans= 0x3f3f3f3f;
struct edge {
	int to, nexty, dis;
} eds[1001];
void add(int a, int b, int c) {
	eds[edptr].to= b, eds[edptr].nexty= head[a], eds[edptr].dis= c;
	head[a]= edptr++;
	return;
}
int f[301], rt, dis[301], mark[301];
void dfs(int nown, int fa) {
	f[nown]= fa;
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == fa || mark[to]) continue;
		dis[to]= dis[nown] + eds[i].dis;
		dfs(to, nown);
	}
	return;
}
int main() {
	cin >> n >> s;
	for(int i= 1; i < n; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		add(tmpx, tmpy, tmpz), add(tmpy, tmpx, tmpz);
	}
	dfs(1, 0);
	for(int i= 1; i <= n; i++)
		if(dis[i] > dis[rt]) rt= i;
	dis[rt]= 0, dfs(rt, 0);
	for(int i= 1; i <= n; i++)
		if(dis[i] > dis[rt]) rt= i;
	for(int i= rt, j= rt; i; i= f[i]) {
		while(dis[j] - dis[i] > s) j= f[j];
		ans= min(ans, max(dis[rt] - dis[j], dis[i]));
	}
	for(int i= rt; i; i= f[i]) mark[i]= 1;
	for(int i= rt; i; i= f[i]) dis[i]= 0, dfs(i, f[i]);
	for(int i= 1; i <= n; i++) ans= max(ans, dis[i]);
	cout << ans << endl;
	return 0;
}