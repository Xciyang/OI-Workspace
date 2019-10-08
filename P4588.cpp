#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int t, q, p, tmpx;
long long tmpy, v[400005];
void update(int nown, int l, int r, int mlr, long long c) {
	if(l == r) {
		v[nown]= c % p;
		return;
	}
	int mid= (l + r) >> 1;
	if(mid >= mlr)
		update(nown << 1, l, mid, mlr, c);
	else
		update(nown << 1 | 1, mid + 1, r, mlr, c);
	v[nown]= v[nown << 1] * v[nown << 1 | 1] % p;
	return;
}
long long query(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) return v[nown];
	int mid= (l + r) >> 1;
	long long res= 1;
	if(mid >= ml) res= (res * query(nown << 1, l, mid, ml, mr)) % p;
	if(mid < mr) res= (res * query(nown << 1 | 1, mid + 1, r, ml, mr)) % p;
	return res;
}
int main() {
	cin >> t;
	while(t--) {
		cin >> q >> p;
		for(int i= 1; i <= (q << 2); i++) v[i]= 1;
		for(int i= 1; i <= q; i++) {
			cin >> tmpx >> tmpy;
			if(tmpx == 1) {
				update(1, 1, q, i, tmpy);
				cout << query(1, 1, q, 1, i) << endl;
			}
			else {
				update(1, 1, q, tmpy, 1);
				cout << query(1, 1, q, 1, i) << endl;
			}
		}
	}
	return 0;
}