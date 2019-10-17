#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, n1, n2;
long long ans;
struct NODE {
	int id, pre;
	inline int operator<(const NODE &n2) const {
		return pre > n2.pre;
	}
} a[100005];
int va[500005], vb[500005], vc[500005], lazyz[500005];
void pushd(int nown, int l, int r, int mid) {
	if(lazyz[nown] == 1)
		va[nown << 1]= (mid - l + 1 - vc[nown << 1]), vb[nown << 1]= 0, va[nown << 1 | 1]= (r - mid - vc[nown << 1 | 1]), vb[nown << 1 | 1]= 0;
	else if(lazyz[nown] == 2)
		vb[nown << 1]= (mid - l + 1 - vc[nown << 1]), va[nown << 1]= 0, vb[nown << 1 | 1]= (r - mid - vc[nown << 1 | 1]), va[nown << 1 | 1]= 0;
	else if(lazyz[nown] == 3)
		va[nown << 1]= vb[nown << 1]= va[nown << 1 | 1]= vb[nown << 1 | 1]= 0, vc[ntown << 1]= (mid - l + 1), vc[nown << 1 | 1]= (r - mid);
	lazyz[nown << 1]= lazyz[nown << 1 | 1]= lazyz[nown], lazyz[nown]= 0;
	return;
}
void update(int nown, int l, int r, int ml, int mr, int c) {
	if(ml > mr) return;
	if(ml <= l && r <= mr) {
		if(c == 1)
			va[nown]= (r - l + 1 - vc[nown]), vb[nown]= 0;
		else if(c == 2)
			vb[nown]= (r - l + 1 - vc[nown]), va[nown]= 0;
		else if(c == 3)
			va[nown]= vb[nown]= 0, vc[nown]= (r - l + 1);
		lazyz[nown]= c;
		return;
	}
	int mid= (l + r) >> 1;
	if(lazyz[nown]) pushd(nown, l, r, mid);
	if(mid >= ml) update(nown << 1, l, mid, ml, mr, c);
	if(mid < mr) update(nown << 1 | 1, mid + 1, r, ml, mr, c);
	va[nown]= va[nown << 1] + va[nown << 1 | 1], vb[nown]= vb[nown << 1] + vb[nown << 1 | 1], vc[nown]= vc[nown << 1] + vc[nown << 1 | 1];
	return;
}
int query(int nown, int l, int r, int mlr) {
	if(l == r) return va[nown] ? 1 : 2;
	int mid= (l + r) >> 1;
	if(lazyz[nown]) pushd(nown, l, r, mid);
	if(mid >= mlr) return query(nown << 1, l, mid, mlr);
	return query(nown << 1 | 1, mid + 1, r, mlr);
}
int query(int nown, int l, int r, int ml, int mr, int c) {
	if(ml > mr) return 0;
	if(ml <= l && r <= mr) return c == 1 ? va[nown] : vb[nown];
	int mid= (l + r) >> 1, res= 0;
	if(lazyz[nown]) pushd(nown, l, r, mid);
	if(mid >= ml) res+= query(nown << 1, l, mid, ml, mr, c);
	if(mid < mr) res+= query(nown << 1 | 1, mid + 1, r, ml, mr, c);
	return res;
}
int main() {
	cin >> n1 >> n2, n= n1 + n2;
	for(int i= 1; i <= n; i++) {
		cin >> a[i].pre;
		if(i > n1) {
			a[i].id= i;
		}
		else {
			a[i].id= n1 - i + 1;
		}
	}
	update(1, 1, n, 1, n1, 1), update(1, 1, n, n1 + 1, n, 2);
	sort(a + 1, a + n + 1);
	for(int i= 1; i <= n; i++) {
		int x= query(1, 1, n, a[i].id);
		if(x == 1) {
			ans+= query(1, 1, n, a[i].id, n, 1) - 1;
			update(1, 1, n, a[i].id, n, 2);
			update(1, 1, n, a[i].id, a[i].id, 3);
		}
		else {
			ans+= query(1, 1, n, 1, a[i].id, 2) - 1;
			update(1, 1, n, 1, a[i].id, 1);
			update(1, 1, n, a[i].id, a[i].id, 3);
		}
	}
	cout << ans << endl;
	return 0;
}