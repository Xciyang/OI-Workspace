#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
int n, m, a[100005];
priority_queue< pair< int, int > > qu;
long long ans;
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) cin >> a[i], ans+= a[i], qu.push(make_pair(a[i] - a[i] / 2, i));
	for(int i= 1, nown; i <= m; i++) {
		ans-= qu.top().first, nown= qu.top().second, qu.pop();
		a[nown]/= 2, qu.push(make_pair(a[nown] - a[nown] / 2, nown));
	}
	cout << ans << endl;
	return 0;
}