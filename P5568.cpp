#include <iostream>
#include <stdio.h>
using namespace std;
#define N 132000
char opt, lo, ro, tmpx;
int ln, rn;
int v[(N + 10) << 2];
void build(int nown, int l, int r) {
	if(l == r) return;
	v[nown] = -1;
	int mid = (l + r) >> 1;
	build(nown << 1, l, mid);
	build(nown << 1 | 1, mid + 1, r);
}
void pushd(int nown) {
	if(v[nown] == 3) {
		if(v[nown << 1] == -1)
			v[nown << 1] = 3;
		else if(v[nown << 1] == 3)
			v[nown << 1] = -1;
		else
			v[nown << 1] ^= 1;
		if(v[nown << 1 | 1] == -1)
			v[nown << 1 | 1] = 3;
		else if(v[nown << 1 | 1] == 3)
			v[nown << 1 | 1] = -1;
		else
			v[nown << 1 | 1] ^= 1;
	}
	else {
		v[nown << 1] = v[nown << 1 | 1] = v[nown];
	}
	v[nown] = -1;
	return;
}
void updateU(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) {
		v[nown] = 1;
		return;
	}
	if(v[nown] != -1) pushd(nown);
	int mid = (l + r) >> 1;
	if(mid >= ml) updateU(nown << 1, l, mid, ml, mr);
	if(mid < mr) updateU(nown << 1 | 1, mid + 1, r, ml, mr);
	return;
}
void updateD(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) {
		v[nown] = 0;
		return;
	}
	if(v[nown] != -1) pushd(nown);
	int mid = (l + r) >> 1;
	if(mid >= ml) updateD(nown << 1, l, mid, ml, mr);
	if(mid < mr) updateD(nown << 1 | 1, mid + 1, r, ml, mr);
	return;
}
void updateV(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) {
		if(v[nown] == -1)
			v[nown] = 3;
		else if(v[nown] == 3)
			v[nown] = -1;
		else
			v[nown] ^= 1;
		return;
	}
	if(v[nown] != -1) pushd(nown);
	int mid = (l + r) >> 1;
	if(mid >= ml) updateV(nown << 1, l, mid, ml, mr);
	if(mid < mr) updateV(nown << 1 | 1, mid + 1, r, ml, mr);
	return;
}
int query(int nown, int l, int r, int mlr) {
	if(l == r) return v[nown];
	if(v[nown] != -1) pushd(nown);
	int mid = (l + r) >> 1;
	if(mid >= mlr) return query(nown << 1, l, mid, mlr);
	return query(nown << 1 | 1, mid + 1, r, mlr);
}
int main() {
	build(1, 1, N);
	while(cin >> opt) {
		cin >> lo >> ln >> tmpx >> rn >> ro;
		ln = (ln << 1) + (lo == '(') + 1;
		rn = (rn << 1) + (ro == ']');
		if(opt == 'U') {
			updateU(1, 1, N, ln, rn);
		}
		else if(opt == 'I') {
			if(ln > 1) updateD(1, 1, N, 1, ln - 1);
			if(rn < N) updateD(1, 1, N, rn + 1, N);
		}
		else if(opt == 'D') {
			updateD(1, 1, N, ln, rn);
		}
		else if(opt == 'C') {
			if(ln > 1) updateD(1, 1, N, 1, ln - 1);
			if(rn < N) updateD(1, 1, N, rn + 1, N);
			updateV(1, 1, N, ln, rn);
		}
		else {
			updateV(1, 1, N, ln, rn);
		}
	}
	int f = 0, ff = 0;
	for(int i = 1; i <= N; i++) {
		if(query(1, 1, N, i)) {
			if(!f) {
				cout << ((i & 1) ? '[' : '(') << ((i - 1) >> 1) << ',';
				ff = f = 1;
			}
		}
		else {
			if(f) {
				cout << ((i - 1) >> 1) << ((i & 1) ? ')' : ']') << ' ';
				f = 0;
			}
		}
	}
	if(!ff) {
		cout << "empty set" << endl;
	}
	return 0;
}