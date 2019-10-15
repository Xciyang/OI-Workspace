#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m, k, a[100005], f[1005][1005], sum[100005], ans= 0x3f3f3f3f;
int check(int x) {
	memset(sum, 0, sizeof(sum));
	for(int i= 1; i <= n; i++) sum[i]= sum[i - 1] + (a[i] + x) % m;
	memset(f, 0x3f, sizeof(f));
	for(int i= 1; i <= n; i++) f[i][1]= sum[i];
	for(int j= 2; j <= k; j++) {
		for(int i= j; i <= n; i++) {
			for(int l= j - 1; l < i; l++) f[i][j]= min(f[i][j], max(f[l][j - 1], sum[i] - sum[l]));
		}
	}
	return f[n][k];
}
int main() {
	cin >> n >> m >> k;
	for(int i= 1; i <= n; i++) cin >> a[i];
	for(int i= 0; i < m; i++) ans= min(ans, check(i));
	cout << ans << endl;
	return 0;
}