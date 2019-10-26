#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, f[205][205][205], ans;
int f2[205];
const int mod= 998244353;
int main() {
	cin >> n >> m;
	++n;
	f2[0]= 1;
	for(int i= 1; i <= n; i++) f2[i]= (1ll * f2[i - 1] * f2[i - 1] + 2) % mod;
	f[1][1][0]= 1;
	for(int k= 0; k <= m; k++) {
		for(int i= 1; i <= n; i++) {
			for(int j= 1; j <= n; j++) {
				if(i == 1 && j == 1) continue;
				f[i][j][k]= ((long long)f[i - 1][j][k] + f[i][j - 1][k] + (k ? f[i - 1][j - 1][k - 1] : 0)) % mod;
			}
		}
	}
	for(int j= 1; j <= n; j++) {
		int res= 0;
		for(int i= 0; i <= m; i++) res= (res + 1ll * f[j][j][i]) % mod;
		ans= (ans + 1ll * res * f2[j - 1]) % mod;
	}
	cout << ans << endl;
	return 0;
}