#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, k, a[105], c[105], ans;
const int p = 1e9 + 7;
int main() {
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1, greater< int >());
	for(int i = 1; i <= n; i++) cin >> c[i];
	sort(c + 1, c + n + 1);
	if(n == k) {
		for(int i = 1; i <= n; i++) ans = 1LL * ans * i % p;
	}
	else {
		do {
			int minx = 0x3f3f3f3f, maxx = ~0x3f3f3f3f;
			for(int i = 1; i <= k; i++) minx = min(minx, a[i] + c[i]);
			for(int i = k + 1; i <= n; i++) maxx = max(maxx, a[i] + c[i]);
			ans += (minx >= maxx);
		} while(next_permutation(c + 1, c + n + 1));
	}
	cout << ans << endl;
	return 0;
}