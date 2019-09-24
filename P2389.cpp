#include <iostream>
#include <stdio.h>
using namespace std;
int n, k, f[505][505][2], a[505], ans;
int main() {
	cin >> n >> k;
	for(int i= 1; i <= n; i++) cin >> a[i];
	for(int i= 1; i <= n; i++) {
		for(int k= 1; k <= i; k++) {
			f[i][k][0]= max(f[i - 1][k][0], f[i - 1][k][1]);
			f[i][k][1]= max(f[i - 1][k - 1][0], f[i - 1][k][1]) + a[i];
		}
	}
	for(int i= 1; i <= k; i++) ans= max(ans, max(f[n][i][0], f[n][i][1]));
	cout << ans << endl;
	return 0;
}