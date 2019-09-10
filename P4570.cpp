#include <iostream>
#include <stdio.h>
#include <algorithm>
#define int long long
using namespace std;
int n, ans;
struct stone {
	int num, mag;
	bool operator<(const stone &s2) const {
		return mag > s2.mag;
	}
} sts[1001];
int base[64];
int insert(int x) {
	for(int i= 63; i > -1; i--) {
		if(x & (1ll << i)) {
			if(!base[i]) {
				base[i]= x;
				return 1;
			}
			x^= base[i];
		}
	}
	return 0;
}
signed main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> sts[i].num >> sts[i].mag;
	sort(sts + 1, sts + n + 1);
	for(int i= 1; i <= n; i++) {
		if(insert(sts[i].num)) ans+= sts[i].mag;
	}
	cout << ans << endl;
	return 0;
}