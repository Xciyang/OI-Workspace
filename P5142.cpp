#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, p= 1e9 + 7, b[100003], sumb[400003], sumpb[400003], tmpx, tmpy, tmpz, tmps, tmpp;
int qpower(int x) {
	int ans= 1, mi= p - 2;
	while(mi) {
		if(mi & 1) ans= (long long)ans * x % p;
		x= (long long)x * x % p, mi>>= 1;
	}
	return ans;
}
int sqrti(int x) {
	return (long long)x * x % p;
}
void build(int nown, int l, int r) {
	if(l == r) {
		sumb[nown]= b[l], sumpb[nown]= sqrti(b[l]);
		return;
	}
	int mid= (l + r) >> 1;
	build(nown << 1, l, mid), build(nown << 1 | 1, mid + 1, r);
	sumb[nown]= (sumb[nown << 1] + sumb[nown << 1 | 1]) % p, sumpb[nown]= (sumpb[nown << 1] + sumpb[nown << 1 | 1]) % p;
	return;
}
void updateD(int nown, int l, int r, int md) {
	if(l == r) {
		sumb[nown]= b[md], sumpb[nown]= sqrti(b[md]);
		return;
	}
	int mid= (l + r) >> 1;
	if(md <= mid)
		updateD(nown << 1, l, mid, md);
	else
		updateD(nown << 1 | 1, mid + 1, r, md);
	sumb[nown]= (sumb[nown << 1] + sumb[nown << 1 | 1]) % p, sumpb[nown]= (sumpb[nown << 1] + sumpb[nown << 1 | 1]) % p;
	return;
}
int queryS(int nown, int l, int r, int ml, int mr, int *sums) {
	if(ml <= l && r <= mr) return sums[nown];
	int mid= (l + r) >> 1, ans= 0;
	if(mid >= ml) ans+= queryS(nown << 1, l, mid, ml, mr, sums) % p;
	if(mid < mr) ans+= queryS(nown << 1 | 1, mid + 1, r, ml, mr, sums) % p;
	return ans % p;
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) cin >> b[i], b[i]%= p;
	build(1, 1, n);
	while(m--) {
		cin >> tmpx >> tmpy >> tmpz;
		if(tmpx == 1) {
			b[tmpy]= tmpz % p;
			updateD(1, 1, n, tmpy);
		}
		else {
			tmps= (long long)queryS(1, 1, n, tmpy, tmpz, sumb) * qpower(tmpz - tmpy + 1) % p;
			tmpp= (long long)queryS(1, 1, n, tmpy, tmpz, sumpb) * qpower(tmpz - tmpy + 1) % p;
			cout << (tmpp - (long long)tmps * tmps % p + p) % p << endl;
		}
	}
	return 0;
}