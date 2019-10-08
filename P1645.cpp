#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, vis[1005], ans;
struct NODE {
	int l, r, g;
	inline int operator<(const NODE &n2) const {
		return r < n2.r;
	};
} a[1005];
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i].l >> a[i].r >> a[i].g;
	sort(a + 1, a + n + 1);
	for(int i= 1; i <= n; i++) {
		int cnt= 0;
		for(int j= a[i].l; j <= a[i].r; j++) cnt+= vis[j];
		if(cnt >= a[i].g) continue;
		for(int k= a[i].r; k >= a[i].l && cnt < a[i].g; k--) {
			if(vis[k]) continue;
			++ans, ++cnt, vis[k]= 1;
		}
	}
	cout << ans << endl;
	return 0;
}