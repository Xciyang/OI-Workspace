#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, q, tmpx, tmpy, tmpz, tmpk, tmpp;
int a[400005], b[400005];
void update(int *v, int nown, int l, int r, int mlr) {
	if(l == r) {
		v[nown]^= 1;
		return;
	}
	int mid= (l + r) >> 1;
	if(mid >= mlr)
		update(v, nown << 1, l, mid, mlr);
	else
		update(v, nown << 1 | 1, mid + 1, r, mlr);
	v[nown]= v[nown << 1] + v[nown << 1 | 1];
	return;
}
int query(int *v, int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) return v[nown];
	int mid= (l + r) >> 1, res= 0;
	if(mid >= ml) res+= query(v, nown << 1, l, mid, ml, mr);
	if(mid < mr) res+= query(v, nown << 1 | 1, mid + 1, r, ml, mr);
	return res;
}
int main() {
	cin >> n >> m >> q;
	while(q--) {
		cin >> tmpx;
		if(tmpx == 1) {
			cin >> tmpx >> tmpy;
			update(a, 1, 1, n, tmpx);
			update(b, 1, 1, m, tmpy);
		}
		else {
			cin >> tmpx >> tmpy >> tmpz >> tmpk;
			int res1= query(a, 1, 1, n, tmpx, tmpz), res2= query(b, 1, 1, m, tmpy, tmpk);
			cout << 1LL * res1 * (tmpk - tmpy + 1) + 1LL * res2 * (tmpz - tmpx + 1) - 1LL * res1 * res2 * 2 << endl;
		}
	}
	return 0;
}