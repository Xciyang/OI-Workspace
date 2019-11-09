#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <string.h>
#include <vector>
#include <queue>
#include <map>
using namespace std;
#define int long long
struct EDGE {
	int x, y, z;
	inline int operator<(const EDGE &e2) const {
		return x < e2.x;
	};
} e[100005];
int n, m;
long long v[400005], lazy[400005];
void pushd(int nown) {
	lazy[nown << 1]= min(lazy[nown << 1], lazy[nown]);
	lazy[nown << 1 | 1]= min(lazy[nown << 1 | 1], lazy[nown]);
	v[nown << 1]= min(v[nown << 1], lazy[nown]);
	v[nown << 1 | 1]= min(v[nown << 1 | 1], lazy[nown]);
	lazy[nown]= 1000000000000000LL;
	return;
}
void update(int nown, int l, int r, int ml, int mr, long long c) {
	if(ml <= l && r <= mr) {
		lazy[nown]= min(lazy[nown], c);
		v[nown]= min(v[nown], c);
		return;
	}
	if(lazy[nown] != 1000000000000000LL) pushd(nown);
	int mid= (l + r) >> 1;
	if(mid >= ml) update(nown << 1, l, mid, ml, mr, c);
	if(mid < mr) update(nown << 1 | 1, mid + 1, r, ml, mr, c);
	return;
}
long long query(int nown, int l, int r, int mlr) {
	if(l == r) return v[nown];
	if(lazy[nown] != 1000000000000000LL) pushd(nown);
	int mid= (l + r) >> 1;
	if(mid >= mlr) return query(nown << 1, l, mid, mlr);
	return query(nown << 1 | 1, mid + 1, r, mlr);
}
signed main() {
	for(int i= 1; i <= 400000; i++) v[i]= lazy[i]= 1000000000000000LL;
	cin >> n >> m;
	for(int i= 1; i <= m; i++) {
		cin >> e[i].x >> e[i].y >> e[i].z;
	}
	update(1, 1, n, 1, 1, 0);
	sort(e + 1, e + m + 1);
	for(int i= 1; i <= m; i++) {
		update(1, 1, n, e[i].x, e[i].y, query(1, 1, n, e[i].x) + e[i].z);
	}
	int res= query(1, 1, n, n);
	if(res == 1000000000000000LL) res= -1;
	cout << res << endl;
	return 0;
}