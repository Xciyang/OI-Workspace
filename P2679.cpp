#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m, k, f[2][205][205][2];
char tmpa[1005], tmpb[1005];
int main() {
	cin >> n >> m >> k >> (tmpa + 1) >> (tmpb + 1);
	f[0][0][0][0]= f[1][0][0][0]= 1;
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) {
			for(int l= 1; l <= k; l++) {
				f[i & 1][j][l][0]= (f[(i & 1) ^ 1][j][l][0] + f[(i & 1) ^ 1][j][l][1]) % 1000000007;
				f[i & 1][j][l][1]= (tmpa[i] == tmpb[j] ? ((f[(i & 1) ^ 1][j - 1][l - 1][0] + f[(i & 1) ^ 1][j - 1][l][1]) % 1000000007 + f[(i & 1) ^ 1][j - 1][l - 1][1]) % 1000000007 : 0);
			}
		}
	}
	cout << (f[n & 1][m][k][0] + f[n & 1][m][k][1]) % 1000000007 << endl;
	return 0;
}