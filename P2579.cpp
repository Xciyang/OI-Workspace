#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m, a[500005], tmpx, tmpy, tmpz;
int lsum[2000005], rsum[2000005], sum[2000005], ans[2000005];
void pu(int nown) {
	lsum[nown]= max(lsum[nown << 1], sum[nown << 1] + lsum[nown << 1 | 1]);
	rsum[nown]= max(rsum[nown << 1 | 1], rsum[nown << 1] + sum[nown << 1 | 1]);
	sum[nown]= sum[nown << 1] + sum[nown << 1 | 1];
	ans[nown]= max(max(ans[nown << 1], ans[nown << 1 | 1]), max(rsum[nown << 1] + lsum[nown << 1 | 1], max(lsum[nown], rsum[nown])));
	return;
}
void build(int nown, int l, int r) {
	if(l == r) {
		ans[nown]= lsum[nown]= rsum[nown]= sum[nown]= a[l];
		return;
	}
	int mid= (l + r) >> 1;
	build(nown << 1, l, mid), build(nown << 1 | 1, mid + 1, r);
	pu(nown);
	return;
}
void update(int nown, int l, int r, int mlr) {
	if(l == r) {
		ans[nown]= lsum[nown]= rsum[nown]= sum[nown]= a[l];
		return;
	}
	int mid= (l + r) >> 1;
	if(mid >= mlr)
		update(nown << 1, l, mid, mlr);
	else
		update(nown << 1 | 1, mid + 1, r, mlr);
	pu(nown);
	return;
}
struct NODE {
	int sum, lsum, rsum, ans;
};
NODE query(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) return NODE{sum[nown], lsum[nown], rsum[nown], ans[nown]};
	int mid= (l + r) >> 1;
	if(mid >= ml && mid < mr) {
		NODE ans;
		NODE tmpa= query(nown << 1, l, mid, ml, mr);
		NODE tmpb= query(nown << 1 | 1, mid + 1, r, ml, mr);
		ans.sum= tmpa.sum + tmpb.sum;
		ans.lsum= max(tmpa.lsum, tmpa.sum + tmpb.lsum);
		ans.rsum= max(tmpb.rsum, tmpa.rsum + tmpb.sum);
		ans.ans= max(max(tmpa.ans, tmpb.ans), max(tmpa.rsum + tmpb.lsum, max(ans.lsum, ans.rsum)));
		return ans;
	}
	if(mid >= ml) return query(nown << 1, l, mid, ml, mr);
	return query(nown << 1 | 1, mid + 1, r, ml, mr);
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) cin >> a[i];
	build(1, 1, n);
	while(m--) {
		cin >> tmpx >> tmpy >> tmpz;
		if(tmpx == 1) {
			if(tmpy > tmpz) swap(tmpy, tmpz);
			cout << query(1, 1, n, tmpy, tmpz).ans << endl;
		}
		else {
			a[tmpy]= tmpz;
			update(1, 1, n, tmpy);
		}
	}
	return 0;
}