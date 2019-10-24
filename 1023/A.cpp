#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N= 2e5 + 5;
int n, h[N], T;
long long ans;
struct NODE {
	int id, hi;
	inline int operator<(const NODE &n2) const {
		return hi < n2.hi;
	}
} a[N];
int ll[N << 2], rr[N << 2], lazyl[N << 2], lazyr[N << 2];
inline void pushd(int nown) {
	if(lazyr[nown]) {
		lazyr[nown << 1]= lazyr[nown << 1 | 1]= lazyr[nown];
		rr[nown << 1]= rr[nown << 1 | 1]= lazyr[nown];
		lazyr[nown]= 0;
	}
	if(lazyl[nown]) {
		lazyl[nown << 1]= lazyl[nown << 1 | 1]= lazyl[nown];
		ll[nown << 1]= ll[nown << 1 | 1]= lazyl[nown];
		lazyl[nown]= 0;
	}
	return;
}
inline int query(int nown, int l, int r, int mlr, int c) {
	if(mlr < l || r < mlr) return 0;
	if(l == r) return c ? rr[nown] : ll[nown];
	pushd(nown);
	int mid= (l + r) >> 1;
	if(mid >= mlr) return query(nown << 1, l, mid, mlr, c);
	return query(nown << 1 | 1, mid + 1, r, mlr, c);
}
inline void update(int nown, int l, int r, int ml, int mr, int x, int c) {
	if(ml > mr) return;
	if(ml <= l && r <= mr) {
		if(!x)
			ll[nown]=lazyl[nown]= c;
		else
			rr[nown]= lazyr[nown]= c;
		return;
	}
	pushd(nown);
	int mid= (l + r) >> 1;
	if(mid >= ml) update(nown << 1, l, mid, ml, mr, x, c);
	if(mid < mr) update(nown << 1 | 1, mid + 1, r, ml, mr, x, c);
	return;
}
int main() {
	scanf("%d", &n);
	for(int i= 1; i <= n; i++) scanf("%d", &h[i]), ans+= 1ll * h[i] * (n - 1) + 1ll * (2 * i - n - 1) * i;
	scanf("%d", &T);
	for(int i= 1; i <= n; i++) a[i].id= i, a[i].hi= h[i];
	sort(a + 1, a + n + 1);
	lazyl[1]= 1, lazyr[1]= n;
	for(int i= 1; i <= n; i++) {
		int tmpx= query(1, 1, n, a[i].id, 0);
		if(!tmpx || tmpx > a[i].id) continue;
		int tmpy= query(1, 1, n, a[i].id, 1);
		if(!tmpy || tmpy < a[i].id) continue;
		ans-= (1LL * (a[i].id - tmpx + 1) * (tmpy - a[i].id + 1) - 1) * a[i].hi * 2;
		update(1, 1, n, a[i].id, tmpy, 0, a[i].id + 1);
		update(1, 1, n, tmpx, a[i].id, 1, a[i].id - 1);
	}
	printf("%lld\n", ans);
	return 0;
}
