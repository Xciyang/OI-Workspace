#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <queue>
using namespace std;
int n, a[3005], dis[3005][3005], ans = 0;
int v[200005];
void build(int nown, int l, int r) {
	v[nown] = 0x3f3f3f3f;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(nown << 1, l, mid), build(nown << 1 | 1, mid + 1, r);
	return;
}
void pd(int nown) {
	v[nown << 1] = min(v[nown << 1], v[nown]);
	v[nown << 1 | 1] = min(v[nown << 1 | 1], v[nown]);
	v[nown] = 0x3f3f3f3f;
	return;
}
void update(int nown, int l, int r, int ml, int mr, int c) {
	if(ml <= l && r <= mr) {
		v[nown] = min(v[nown], c);
		return;
	}
	int mid = (l + r) >> 1;
	if(v[nown] != 0x3f3f3f3f) pd(nown);
	if(mid >= ml) update(nown << 1, l, mid, ml, mr, c);
	if(mid < mr) update(nown << 1 | 1, mid + 1, r, ml, mr, c);
	return;
}
int query(int nown, int l, int r, int mlr) {
	if(l == r) return v[nown];
	int mid = (l + r) >> 1;
	if(v[nown] != 0x3f3f3f3f) pd(nown);
	if(mid >= mlr) return query(nown << 1, l, mid, mlr);
	return query(nown << 1 | 1, mid + 1, r, mlr);
}
void BFS(int x) {
	queue< int > qu;
	build(1, 1, n);
	update(1, 1, n, x, x, dis[x][x] = 1);
	qu.push(x);
	register int nown, d;
	while(!qu.empty()) {
		nown = qu.front(), dis[x][nown] = query(1, 1, n, nown), qu.pop();
		update(1, 1, n, max(1, nown - a[nown]), min(nown + a[nown], n), dis[x][nown] + 1);
		if(nown - 1 >= 1 && !dis[x][nown - 1]) qu.push(nown - 1);
		if(nown + 1 <= n && !dis[x][nown + 1]) qu.push(nown + 1);
	}
	for(int i = 1; i <= n; i++) --dis[x][i];
	return;
}
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) BFS(i);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) ans = max(ans, min(dis[i][j], dis[j][i]));
	cout << ans << endl;
	return 0;
}