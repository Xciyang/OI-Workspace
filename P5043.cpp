#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int m, n, tmpx;
vector< int > edg[55];
unsigned long long ans[55][55];
const unsigned long long p = 1007;
unsigned long long mhash(int nown, int fa) {
	unsigned long long a[55], ap = 0;
	for(int i = 0; i < edg[nown].size(); i++) {
		if(edg[nown][i] == fa) continue;
		a[++ap] = mhash(edg[nown][i], nown);
	}
	sort(a + 1, a + ap + 1);
	unsigned long long res = 0;
	for(int i = 1; i <= ap; i++) res = res * p + a[i];
	return res + p - 1;
}
int main() {
	cin >> m;
	for(int mm = 1; mm <= m; mm++) {
		cin >> n;
		for(int i = 0; i <= n; i++) edg[i].clear();
		for(int i = 1; i <= n; i++) {
			cin >> tmpx;
			if(tmpx) {
				edg[tmpx].push_back(i);
				edg[i].push_back(tmpx);
			}
		}
		for(int i = 1; i <= n; i++) ans[mm][i] = mhash(i, 0);
		sort(ans[mm] + 1, ans[mm] + n + 1);
		for(int i = 1, j; i <= mm; i++) {
			for(j = 1; j <= n; j++) {
				if(ans[i][j] != ans[mm][j]) break;
			}
			if(j > n) {
				cout << i << endl;
				break;
			}
		}
	}
	return 0;
}