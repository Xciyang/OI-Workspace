#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
using namespace std;
int n, m, maxh[15], maxw[15], a[15][15], b[15][15];
map< long long, int > mm;
inline long long mhash() {
	long long res = 0;
	for(int i = 1; i <= n; i++) {
		res = res * m + maxh[i];
	}
	return res;
}
int dfs(int w) {
	long long hs = mhash();
	if(mm.count(hs)) return mm[hs];
	int maxx = -0x3f3f3f3f;
	for(int i = 1; i <= n; i++) {
		int x = maxh[i] + 1;
		if(x <= m && maxw[x] == i - 1) {
			++maxh[i], ++maxw[x];
			maxx = max(maxx, (w ? a[i][x] : b[i][x]) - dfs(w ^ 1));
			--maxh[i], --maxw[x];
		}
	}
	if(maxx == -0x3f3f3f3f) maxx = 0;
	return mm[hs] = maxx;
}
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> b[i][j];
		}
	}
	cout << dfs(1) << endl;
	return 0;
}