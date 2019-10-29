#include <iostream>
#include <stdio.h>
using namespace std;
int n, k, s[505], gpptr, ans;
struct GROUP {
	int maxs, mins;
} gps[505];
void dfs(int nown, int sum) {
	if(sum > k) return;
	if(nown == n + 1) {
		++ans;
		return;
	}
	for(int i= 1; i <= gpptr; i++) {
		GROUP last= gps[i];
		gps[i].maxs= max(gps[i].maxs, s[nown]);
		gps[i].mins= min(gps[i].mins, s[nown]);
		dfs(nown + 1, sum - (last.maxs - last.mins) + (gps[i].maxs - gps[i].mins));
		gps[i]= last;
	}
	++gpptr;
	gps[gpptr].maxs= gps[gpptr].mins= s[nown];
	dfs(nown + 1, sum);
	--gpptr;
	return;
}
int main() {
	cin >> n >> k;
	for(int i= 1; i <= n; i++) cin >> s[i];
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}