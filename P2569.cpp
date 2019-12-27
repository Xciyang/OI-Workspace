#include <iostream>
#include <stdio.h>
#include <queue>
#include <string.h>
using namespace std;
int t, p, w, as, bs;
long long ans, f[2005][2005], ap, bp;
int main() {
	cin >> t >> p >> w;
	memset(f, ~0x3f, sizeof(f));
	for(int i = 1; i <= t; i++) {
		cin >> ap >> bp >> as >> bs;
		for(int j = 0; j <= p; j++) f[i][j] = max(f[i][j], f[i - 1][j]);
		for(int j = 0; j <= as; j++) f[i][j] = max(f[i][j], -j * ap);
		// i <= w + 1
		if(i <= w) continue;
		deque< int > qu, qu2;
		for(int j = 0; j <= p; j++) {
			while(!qu.empty() && qu.front() < j - as) qu.pop_front();
			while(!qu.empty() && f[i - w - 1][qu.back()] + qu.back() * ap <= f[i - w - 1][j] + j * ap) qu.pop_back();
			qu.push_back(j);
			f[i][j] = max(f[i][j], f[i - w - 1][qu.front()] + qu.front() * ap - j * ap);
		}
		for(int j = p; j >= 0; j--) {
			while(!qu2.empty() && qu2.front() > j + bs) qu2.pop_front();
			while(!qu2.empty() && f[i - w - 1][qu2.back()] + qu2.back() * bp <= f[i - w - 1][j] + j * bp) qu2.pop_back();
			qu2.push_back(j);
			f[i][j] = max(f[i][j], f[i - w - 1][qu2.front()] + qu2.front() * bp - j * bp);
		}
	}
	for(int i = 0; i <= p; i++) ans = max(ans, f[t][i]);
	cout << ans << endl;
	return 0;
}