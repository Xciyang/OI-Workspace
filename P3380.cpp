#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#define INF 2147483647
using namespace std;
int n, m, a[50004], tmpx, tmpy, tmpz, tmpk;
vector< int > v[200016];
void insert(int nown, int x) {
	v[nown].insert(upper_bound(v[nown].begin(), v[nown].end(), x), x);
	return;
}
void erase(int nown, int x) {
	auto y = lower_bound(v[nown].begin(), v[nown].end(), x);
	if(y != v[nown].end() && *y == x) v[nown].erase(y);
	return;
}
int smaller(int nown, int x) {
	return lower_bound(v[nown].begin(), v[nown].end(), x) - v[nown].begin();
}
void build(int nown, int l, int r) {
	for(int i = l; i <= r; i++) insert(nown, a[i]);
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(nown << 1, l, mid), build(nown << 1 | 1, mid + 1, r);
	return;
}
int getRank(int nown, int l, int r, int ml, int mr, int x) {
	if(ml <= l && r <= mr) return smaller(nown, x);
	int mid = (l + r) >> 1, res = 0;
	if(mid >= ml) res += getRank(nown << 1, l, mid, ml, mr, x);
	if(mid < mr) res += getRank(nown << 1 | 1, mid + 1, r, ml, mr, x);
	return res;
}
int getVal(int ml, int mr, int x) {
	int l = 0, r = 1e8, res, mid, ans = 1e8;
	while(l <= r) {
		mid = (l + r) >> 1, res = getRank(1, 1, n, ml, mr, mid) + 1;
		if(res <= x)
			l = mid + 1, ans = mid;
		else
			r = mid - 1;
	}
	return ans;
}
void erase(int nown, int l, int r, int mlr, int x) {
	erase(nown, x);
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(mid >= mlr)
		erase(nown << 1, l, mid, mlr, x);
	else
		erase(nown << 1 | 1, mid + 1, r, mlr, x);
	return;
}
void insert(int nown, int l, int r, int mlr, int x) {
	insert(nown, x);
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(mid >= mlr)
		insert(nown << 1, l, mid, mlr, x);
	else
		insert(nown << 1 | 1, mid + 1, r, mlr, x);
	return;
}
int pre(int nown, int x) {
	auto y = lower_bound(v[nown].begin(), v[nown].end(), x);
	if(y == v[nown].begin()) return -INF;
	return *--y;
}
int pre(int nown, int l, int r, int ml, int mr, int x) {
	if(ml <= l && r <= mr) return pre(nown, x);
	int mid = (l + r) >> 1, res = -INF;
	if(mid >= ml) res = max(res, pre(nown << 1, l, mid, ml, mr, x));
	if(mid < mr) res = max(res, pre(nown << 1 | 1, mid + 1, r, ml, mr, x));
	return res;
}
int nxt(int nown, int x) {
	auto y = upper_bound(v[nown].begin(), v[nown].end(), x);
	if(y == v[nown].end()) return INF;
	return *y;
}
int nxt(int nown, int l, int r, int ml, int mr, int x) {
	if(ml <= l && r <= mr) return nxt(nown, x);
	int mid = (l + r) >> 1, res = INF;
	if(mid >= ml) res = min(res, nxt(nown << 1, l, mid, ml, mr, x));
	if(mid < mr) res = min(res, nxt(nown << 1 | 1, mid + 1, r, ml, mr, x));
	return res;
}
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i];
	build(1, 1, n);
	for(int i = 1; i <= m; i++) {
		cin >> tmpx;
		switch(tmpx) {
			case 1:
				cin >> tmpy >> tmpz >> tmpk;
				cout << getRank(1, 1, n, tmpy, tmpz, tmpk) + 1 << endl;
				break;
			case 2:
				cin >> tmpy >> tmpz >> tmpk;
				cout << getVal(tmpy, tmpz, tmpk) << endl;
				break;
			case 3:
				cin >> tmpy >> tmpz;
				erase(1, 1, n, tmpy, a[tmpy]);
				a[tmpy] = tmpz;
				insert(1, 1, n, tmpy, tmpz);
				break;
			case 4:
				cin >> tmpy >> tmpz >> tmpk;
				cout << pre(1, 1, n, tmpy, tmpz, tmpk) << endl;
				break;
			case 5:
				cin >> tmpy >> tmpz >> tmpk;
				cout << nxt(1, 1, n, tmpy, tmpz, tmpk) << endl;
				break;
			default: break;
		}
	}
	return 0;
}