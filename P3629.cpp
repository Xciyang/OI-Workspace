#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, k, head[100001], edptr= 1, tmpx, tmpy, tmpz, rt1, rt2, sums;
struct edge {
	int to, nexty, dis;
} eds[200001];
void add(int a, int b, int c) {
	eds[edptr].nexty= head[a], eds[edptr].to= b, eds[edptr].dis= c;
	head[a]= edptr++;
	return;
}
int dis[100001];
void dfs(int nown, int fa) {
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == fa) continue;
		dis[to]= dis[nown] + eds[i].dis;
		dfs(to, nown);
	}
	return;
}
int mark(int nown, int fa) {
	if(nown == rt1) return 1;
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == fa) continue;
		if(mark(to, nown)) {
			eds[i].dis= -1;
			return 1;
		}
	}
	return 0;
}
int maxf1, maxf;
void dp(int nown, int fa) {
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == fa) continue;
		dp(to, nown);
		maxf= max(maxf, dis[nown] + dis[to] + eds[i].dis);
		dis[nown]= max(dis[nown], dis[to] + eds[i].dis);
	}
	return;
}
int main() {
	cin >> n >> k;
	for(int i= 1; i < n; i++) {
		cin >> tmpx >> tmpy;
		add(tmpx, tmpy, 1), add(tmpy, tmpx, 1);
	}
	dfs(1, 0);
	for(int i= 1; i <= n; i++)
		if(dis[i] > dis[rt1]) rt1= i;
	dis[rt1]= 0, dfs(rt1, 0);
	for(int i= 1; i <= n; i++)
		if(dis[i] > dis[rt2]) rt2= i;
	if(k == 1) {
		cout << 2 * n - dis[rt2] - 1 << endl;
		return 0;
	}
	maxf1= dis[rt2];
	memset(dis, 0, sizeof(dis));
	mark(rt2, 0), dp(rt2, 0);
	cout << 2 * n - maxf1 - maxf << endl;
	return 0;
}