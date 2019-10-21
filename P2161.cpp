/*
too difficult

but why ?
*/

#include <iostream>
#include <stdio.h>
#include <set>
using namespace std;
int n, tmpx, tmpy, ans;
char tmpt;
struct Range {
	int l, r;
	inline int operator<(const Range &r2) const {
		return r < r2.l;
	}
} range;
set< Range > rs;
// int lazyz[400005], lazyz2[400005];
// int zzl[400005], zzr[400005];
// int sum[400005];
// void pushd(int nown) {
// 	zzl[nown << 1]= zzr[nown << 1]= lazyz[nown];
// 	zzl[nown << 1 | 1]= zzr[nown << 1 | 1]= lazyz[nown];
// 	lazyz[nown << 1]= lazyz[nown << 1 | 1]= lazyz2[nown];
// 	lazyz[nown]= -1;
// 	return;
// }
// inline int query(int nown, int l, int r, int mlr, int c) {
// 	if(l == r) return c ? zzr[nown] : zzl[nown];
// 	if(lazyz[nown] != -1) pushd(nown);
// 	int mid= (l + r) >> 1;
// 	if(mid >= mlr) return query(nown << 1, l, mid, mlr, c);
// 	return query(nown << 1 | 1, mid + 1, r, mlr, c);
// }
// struct NODE {
// 	int sum;
// 	int l, r;
// };
// inline NODE query2(int nown, int l, int r, int ml, int mr) {
// 	if(ml <= l && r <= mr) return NODE{sum[nown], zzl[nown], zzr[nown]};
// 	if(lazyz[nown] != -1) pushd(nown);
// 	int mid= (l + r) >> 1;
// 	if(mid >= ml && mid < mr) {
// 		NODE res1= query2(nown << 1, l, mid, ml, mr);
// 		NODE res2= query2(nown << 1 | 1, mid + 1, r, ml, mr);
// 		return NODE{res1.sum + res2.sum - (), res1.l, res2.r};
// 	}
// 	if(mid >= ml) return query2(nown << 1, l, mid, ml, mr);
// 	return query2(nown << 1 | 1, mid + 1, r, ml, mr);
// }
int main() {
	cin >> n;
	while(n--) {
		cin >> tmpt;
		if(tmpt == 'A') {
			cin >> range.l >> range.r;
			ans= 0;
			set< Range >::iterator it= rs.find(range);
			while(it != rs.end()) {
				++ans, rs.erase(it);
				it= rs.find(range);
			}
			rs.insert(range);
			cout << ans << endl;
			// int x = query(1, 1, 100005, tmpx, tmpy);
			// int y =
		}
		else {
			cout << rs.size() << endl;
		}
	}
	return 0;
}