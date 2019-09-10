#include <iostream>
#include <stdio.h>
using namespace std;
#define int long long
const int mod= 1e9 + 7;
int n, m, ans;
signed main() {
	scanf("%d%d", &n, &m);
	for(int i= 1; i <= n; i++) {
		ans= (ans + i) % mod;
		for(int j= 2, base= n - i; j <= m; j++) ans= (ans + base * i * 2) % mod, base= base * (n - i) % mod;
	}
	printf("%d\n", ans);
	return 0;
}