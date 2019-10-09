#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
char tmpc;
int n, k, a[505], f[505][105][105][2], ans;
int main() {
	cin >> n >> k;
	for(int i= 1; i <= n; i++) cin >> tmpc, a[i]= (tmpc == 'z');
	memset(f, ~0x3f, sizeof(f));
	f[1][0][0][a[1]]= f[1][a[1]][!a[1]][!a[1]]= 0;
	for(int i= 2; i <= n; i++) {
		for(int j= 0; j <= i && j <= k; j++) {
			for(int l= 0; l <= i && l <= k; l++) {
				f[i][j][l][a[i]]= max(f[i - 1][j][l][0] + a[i], f[i - 1][j][l][1]);
				if(a[i] && j) f[i][j][l][0]= max(f[i - 1][j - 1][l][0], f[i - 1][j - 1][l][1]);
				if(!a[i] && l) f[i][j][l][1]= max(f[i - 1][j][l - 1][0] + 1, f[i - 1][j][l - 1][1]);
			}
		}
	}
	for(int i= 0; i <= k; i++) ans= max(ans, max(f[n][i][i][0], f[n][i][i][1]));
	cout << ans << endl;
	return 0;
}