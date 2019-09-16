#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
int n, m, k;
int d[1005], ren[1005], tmpx, tmpy, tmpz, a[1005], maxx[1005], ans;
struct NODE {
	int l, r, us, val;
	bool operator<(const NODE &n2) const {
		return val < n2.val;
	}
};
priority_queue< NODE > qu;
void fg(int l, int r) {
	if(l >= r) return;
	if(!d[l]) {
		fg(l + 1, r);
		return;
	}
	for(int i= l + 1; i < r; i++) {
		if(a[i] >= maxx[i]) {
			fg(l, i), fg(i, r);
			return;
		}
	}
	int us= d[l], tot= ren[r];
	for(int i= l + 1; i < r; i++) us= min(us, maxx[i] - a[i]), tot+= ren[i];
	d[l]-= us;
	for(int i= l + 1; i < r; i++) maxx[i]-= us;
	qu.push(NODE{l, r, us, tot});
	return;
}
int main() {
	cin >> n >> m >> k;
	for(int i= 1; i < n; i++) cin >> d[i];
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz, ans-= tmpx;
		a[tmpy]= max(a[tmpy], tmpx), ++ren[tmpz];
	}
	for(int i= 1; i <= n; i++) maxx[i]= max(maxx[i - 1], a[i - 1]) + d[i - 1];
	for(int i= 2; i <= n; i++) ans+= maxx[i] * ren[i];
	register int lastl= 1, lastr= n;
	register NODE nown;
	while(k) {
		fg(lastl, lastr);
		if(qu.empty()) break;
		nown= qu.top(), qu.pop();
		ans-= nown.val * min(k, nown.us), k-= min(k, nown.us), lastl= nown.l, lastr= nown.r;
	}
	cout << ans << endl;
	return 0;
}