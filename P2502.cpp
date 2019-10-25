#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, m, bx, ex;
struct EDGE {
	int x, y, z;
	inline int operator<(const EDGE &e2) const {
		return z < e2.z;
	}
} edg[5005];
int fa[505], notwp[505], aptr;
inline int getf(int x) {
	return fa[x] == x ? x : fa[x]= getf(fa[x]);
}
double bestc;
int bestans;
struct ANS {
	int x, y;
} ans[5005];
inline int gcd(int x, int y) {
	return y ? gcd(y, x % y) : x;
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) fa[i]= i;
	for(int i= 1; i <= m; i++) {
		cin >> edg[i].x >> edg[i].y >> edg[i].z;
		int fx= getf(edg[i].x), fy= getf(edg[i].y);
		if(fx == fy) continue;
		fa[fx]= fy;
	}
	cin >> bx >> ex;
	if(getf(bx) != getf(ex)) {
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}
	sort(edg + 1, edg + m + 1);
	for(int i= 1; i <= n; i++) notwp[i]= (getf(i) != getf(bx));
	for(int i= 1; i <= m; i++) {
		if(notwp[edg[i].x] || notwp[edg[i].y]) continue;
		int maxx= edg[i].z, minx= edg[i].z;
		for(int j= 1; j <= n; j++) fa[j]= j;
		for(int j= i; j; j--) {
			int fx= getf(edg[j].x), fy= getf(edg[j].y);
			if(fx == fy) continue;
			fa[fx]= fy, minx= edg[j].z;
			if(getf(bx) == getf(ex)) break;
		}
		if(getf(bx) == getf(ex)) ans[++aptr]= {maxx, minx};
	}
	bestc= 1e9;
	for(int i= 1; i <= aptr; i++)
		if((double)ans[i].x / ans[i].y < bestc) bestc= (double)ans[i].x / ans[i].y, bestans= i;
	if(ans[bestans].x % ans[bestans].y == 0) {
		cout << ans[bestans].x / ans[bestans].y << endl;
	}
	else {
		int gc= gcd(ans[bestans].x, ans[bestans].y);
		cout << ans[bestans].x / gc << '/' << ans[bestans].y / gc << endl;
	}
	return 0;
}