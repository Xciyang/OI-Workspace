#include <iostream>
#include <stdio.h>
#include <algorithm>
#define int long long
using namespace std;
int n, tmpx1, tmpy1, tmpx2, tmpy2, ans;
int Y[300000], m;
struct SEG {
	int x, upp, dow, c;
	bool operator<(const SEG &s2) const {
		return x < s2.x;
	}
} segs[300000];
int len[1500000], sum[1500000];
void pushu(int nown, int l, int r) {
	if(sum[nown] > 0)
		len[nown]= Y[r + 1] - Y[l];
	else
		len[nown]= len[nown << 1] + len[nown << 1 | 1];
	return;
}
void update(int nown, int l, int r, int ml, int mr, int c) {
	if(ml <= l && r <= mr) {
		sum[nown]+= c;
		pushu(nown, l, r);
		return;
	}
	int mid= (l + r) >> 1;
	if(ml <= mid) update(nown << 1, l, mid, ml, mr, c);
	if(mr > mid) update(nown << 1 | 1, mid + 1, r, ml, mr, c);
	pushu(nown, l, r);
	return;
}
signed main() {
	cin >> n;
	for(int i= 1; i <= n; i++) {
		cin >> tmpx1 >> tmpy1 >> tmpx2 >> tmpy2;
		segs[i].upp= segs[n + i].upp= tmpy1;
		segs[i].dow= segs[n + i].dow= tmpy2;
		segs[i].x= tmpx1, segs[n + i].x= tmpx2;
		segs[i].c= 1, segs[n + i].c= -1;
		Y[i]= tmpy1, Y[n + i]= tmpy2;
	}
	sort(Y + 1, Y + n * 2 + 1);
	m= unique(Y + 1, Y + n * 2 + 1) - Y - 1;
	sort(segs + 1, segs + n * 2 + 1);
	for(int i= 1, pos1, pos2; i < n * 2; i++) {
		pos1= lower_bound(Y + 1, Y + m + 1, segs[i].upp) - Y, pos2= lower_bound(Y + 1, Y + m + 1, segs[i].dow) - Y;
		update(1, 1, m, pos1, pos2 - 1, segs[i].c);
		ans+= len[1] * (segs[i + 1].x - segs[i].x);
	}
	cout << ans << endl;
	return 0;
}