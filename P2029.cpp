#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, t, s[5001], b[5001], f[2][5001], ans;
int main() {
	cin >> n >> t;
	for(int i= 1; i <= n; i++) cin >> s[i];
	for(int i= 1; i <= n; i++) cin >> b[i];
	memset(f, ~0x3f, sizeof(f));
	f[0][0]= 0;
	for(int i= 1; i <= n; i++) {
		f[i & 1][0]= f[(i & 1) ^ 1][0] - s[i];
		for(int j= 1; j <= i; j++) {
			f[i & 1][j]= max(f[(i & 1) ^ 1][j - 1] + s[i], f[(i & 1) ^ 1][j] - s[i]);
			if(j % t == 0) f[i & 1][j]= max(f[i & 1][j], f[(i & 1) ^ 1][j - 1] + s[i] + b[i]);
		}
	}
	for(int i= 0; i <= n; i++) ans= max(ans, f[n & 1][i]);
	cout << ans << endl;
	return 0;
}