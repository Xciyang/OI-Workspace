#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, k, f, tmpx, tmpy, fa[255], r[255], p[255][255], ans= 0x3f3f3f3f;
struct NODE {
	int x, y;
} a[255 * 255];
inline int getf(int x) {
	return fa[x] == x ? x : fa[x]= getf(fa[x]);
}
int main() {
	cin >> n >> m >> k >> f;
	for(int i= 1; i <= m; i++) cin >> a[i].x >> a[i].y;
	for(int i= 1; i <= n; i++) fa[i]= i;
	for(int i= 1; i <= f; i++) {
		cin >> tmpx >> tmpy;
		fa[getf(tmpx)]= getf(tmpy);
	}
	for(int i= 1; i <= m; i++) {
		if(!p[getf(a[i].x)][a[i].y]) {
			p[getf(a[i].x)][a[i].y]= 1;
			++r[getf(a[i].x)];
		}
	}
	for(int i= 1; i <= n; i++) {
		ans= min(ans, r[getf(i)]);
	}
	ans= min(ans + k, n);
	cout << ans << endl;
	return 0;
}
/*

*/