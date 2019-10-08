#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, m, tot, tmpx, tmpy;
struct NODE {
	int x, y;
} a[200005];
struct OPT {
	int x, y, z;
} b[200005];
int lc[10000009], rc[10000009], MAIN= 1, cnt= 1;
long long v[10000009], lazyz[10000009];
const long long k= (1LL << 31) - 1;
void pushd(int nown, long long l, long long r) {
	if(!lc[nown]) lc[nown]= ++cnt;
	if(!rc[nown]) rc[nown]= ++cnt;
	long long mid= (l + r) >> 1;
	v[lc[nown]]+= lazyz[nown] * (mid - l + 1), v[rc[nown]]+= lazyz[nown] * (r - mid), lazyz[lc[nown]]+= lazyz[nown], lazyz[rc[nown]]+= lazyz[nown];
	lazyz[nown]= 0;
	return;
}
void update(int &nown, long long l, long long r, long long ml, long long mr, int c) {
	if(!nown) nown= ++cnt;
	if(ml <= l && r <= mr) {
		v[nown]+= c * (r - l + 1), lazyz[nown]+= c;
		return;
	}
	if(lazyz[nown]) pushd(nown, l, r);
	long long mid= (l + r) >> 1;
	if(mid >= ml) update(lc[nown], l, mid, ml, mr, c);
	if(mid < mr) update(rc[nown], mid + 1, r, ml, mr, c);
	v[nown]= v[lc[nown]] + v[rc[nown]];
	return;
}
long long query(int nown, long long l, long long r, long long ml, long long mr) {
	if(!nown) return 0;
	if(ml <= l && r <= mr) {
		return v[nown];
	}
	if(lazyz[nown]) pushd(nown, l, r);
	long long mid= (l + r) >> 1, res= 0;
	if(mid >= ml) res+= query(lc[nown], l, mid, ml, mr);
	if(mid < mr) res+= query(rc[nown], mid + 1, r, ml, mr);
	return res;
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) cin >> a[i].x >> a[i].y;
	for(int i= 1; i <= m; i++) cin >> b[i].x >> b[i].y >> b[i].z;
	for(int i= 1; i <= n; i++) update(MAIN, 1, k, a[i].x, k, a[i].y);
	for(int i= 1; i <= m; i++) {
		if(b[i].x == 1) {
			printf("%.4lf\n", (double)query(MAIN, 1, k, b[i].y, b[i].z) / (b[i].z - b[i].y + 1));
		}
		else {
			update(MAIN, 1, k, b[i].y, k, b[i].z);
		}
	}
	return 0;
}