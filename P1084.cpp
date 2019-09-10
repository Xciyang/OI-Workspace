#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define int long long
using namespace std;
int n, m, head[50001], edptr= 1, tmpx, tmpy, tmpz, arms[50001];
struct edge {
	int to, nexty, dis;
} eds[100001];
void add(int a, int b, int c) {
	eds[edptr].to= b, eds[edptr].nexty= head[a], eds[edptr].dis= c;
	head[a]= edptr++;
	return;
}
int fa[50001][17], dis[50001][17];
void dfs(int nown) {
	for(int i= 1; i < 17; i++) {
		fa[nown][i]= fa[fa[nown][i - 1]][i - 1];
		dis[nown][i]= dis[nown][i - 1] + dis[fa[nown][i - 1]][i - 1];
	}
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == fa[nown][0]) continue;
		fa[to][0]= nown, dis[to][0]= eds[i].dis;
		dfs(to);
	}
	return;
}
int vis[50001], wacnt, hrest[50001], hrestm[50001], wbcnt;
struct DATA {
	int id, rest;
	bool operator<(const DATA &d2) const {
		return rest > d2.rest;
	}
} waita[50001], waitb[50001];
int dfs2(int nown) {
	int nleaves= 0, ok= 1;
	if(vis[nown]) return 1;
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == fa[nown][0]) continue;
		nleaves= 1;
		if(!dfs2(to)) {
			ok= 0;
			if(nown != 1) return 0;
			waitb[++wbcnt].id= to, waitb[wbcnt].rest= eds[i].dis;
		}
	}
	return nleaves && ok;
}
int check(int nowans) {
	memset(vis, 0, sizeof(vis));
	memset(hrest, 0, sizeof(hrest));
	wacnt= wbcnt= 0;
	for(int i= 1; i <= m; i++) {
		tmpx= arms[i], tmpy= 0;
		for(int j= 16; j > -1; j--)
			if(fa[tmpx][j] > 1 && tmpy + dis[tmpx][j] <= nowans) tmpy+= dis[tmpx][j], tmpx= fa[tmpx][j];
		if(fa[tmpx][0] == 1 && tmpy + dis[tmpx][0] <= nowans) {
			waita[++wacnt].id= i, waita[wacnt].rest= nowans - tmpy - dis[tmpx][0];
			if(!hrest[tmpx] || waita[wacnt].rest < hrestm[tmpx]) hrest[tmpx]= i, hrestm[tmpx]= waita[wacnt].rest;
		}
		else
			vis[tmpx]= 1;
	}
	if(dfs2(1)) return 1;
	sort(waita + 1, waita + wacnt + 1), sort(waitb + 1, waitb + wbcnt + 1);
	tmpx= 1;
	memset(vis, 0, sizeof(vis));
	for(int i= 1; i <= wbcnt; i++) {
		if(hrest[waitb[i].id] && !vis[hrest[waitb[i].id]]) {
			vis[hrest[waitb[i].id]]= 1;
			continue;
		}
		while(tmpx <= wacnt && (vis[waita[tmpx].id] || waita[tmpx].rest < waitb[i].rest)) ++tmpx;
		if(tmpx > wacnt) return 0;
		vis[waita[tmpx].id]= 1;
	}
	return 1;
}
signed main() {
	cin >> n;
	for(int i= 1; i < n; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		add(tmpx, tmpy, tmpz), add(tmpy, tmpx, tmpz);
	}
	dfs(1);
	cin >> m;
	for(int i= 1; i <= m; i++) cin >> arms[i];
	int l= 0, r= 500000, mid, ans= -1;
	while(l <= r) {
		mid= (l + r) >> 1;
		if(check(mid))
			r= mid - 1, ans= mid;
		else
			l= mid + 1;
	}
	cout << ans << endl;
	return 0;
}