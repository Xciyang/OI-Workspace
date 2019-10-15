#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, a[50005], v[100005], tmpx, nptr;
long long ans;
inline int lowb(int x) {
	return x & -x;
}
inline int query(int x) {
	int res= 0;
	for(; x; x-= lowb(x)) res+= v[x];
	return res;
}
inline void update(int x, int c) {
	for(; x <= (n << 1); x+= lowb(x)) v[x]+= c;
	return;
}
struct NODE {
	int l, r;
	inline int operator<(const NODE &n2) const {
		return r - l > n2.r - n2.l;
	}
} p[50005];
int main() {
	cin >> n;
	for(int i= 1; i <= (n << 1); i++) {
		cin >> tmpx;
		if(a[tmpx])
			p[++nptr]= {a[tmpx], i};
		else
			a[tmpx]= i;
	}
	sort(p + 1, p + n + 1);
	for(int i= 1; i <= n; i++) {
		ans+= query(p[i].r) - query(p[i].l - 1);
		update(p[i].l, 1), update(p[i].r, 1);
	}
	cout << ans << endl;
	return 0;
}