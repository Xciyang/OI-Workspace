#include <iostream>
#include <stdio.h>
using namespace std;
#define int long long
int n, m, head[50001], edptr= 1, tmpx, tmpy, tmpz, ans;
struct edge {
	int to, nexty, dis;
} eds[200001];
void add(int a, int b, int c) {
	eds[edptr].to= b, eds[edptr].nexty= head[a], eds[edptr].dis= c;
	head[a]= edptr++;
	return;
}
int vis[50001], dis[50001], base[50001];
void insert(int x) {
	for(int j= 63; j > -1; j--) {
		if(x & (1ll << j)) {
			if(!base[j]) base[j]= x;
			x^= base[j];
		}
	}
	return;
}
void dfs(int nown) {
	vis[nown]= 1;
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(!vis[to])
			dis[to]= dis[nown] ^ eds[i].dis, dfs(to);
		else
			insert(dis[to] ^ dis[nown] ^ eds[i].dis);
	}
	return;
}
signed main() {
	cin >> n >> m;
	for(int i= 0; i < m; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		add(tmpx, tmpy, tmpz), add(tmpy, tmpx, tmpz);
	}
	dfs(1);
	ans= dis[n];
	for(int i= 63; i > -1; i--) {
		if(ans < (ans ^ base[i])) ans^= base[i];
	}
	cout << ans << endl;
	return 0;
}