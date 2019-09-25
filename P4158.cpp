#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, t, F[55][55][2555][2], ans;
char ys[55][55];
int main() {
	cin >> n >> m >> t;
	for(int i= 1; i <= n; i++) cin >> (ys[i] + 1);
	for(int k= 1; k <= t; k++) {
		for(int i= 1; i <= n; i++) {
			for(int j= 1; j < i; j++) F[i][0][k][1]= F[i][0][k][0]= max(F[i][0][k][0], max(F[j][m][k - 1][0], F[j][m][k - 1][1]));
			for(int j= 1; j <= m; j++) {
				F[i][j][k][0]= max(F[i][j - 1][k][0] , F[i][j - 1][k - 1][1])+ (ys[i][j] == '0');
				F[i][j][k][1]= max(F[i][j - 1][k][1] , F[i][j - 1][k - 1][0])+ (ys[i][j] == '1');
			}
		}
	}
	for(int i= 1; i <= n; i++)
		for(int j= 1; j <= m; j++)
			for(int k= 1; k <= t; k++) ans= max(ans, max(F[i][j][k][0], F[i][j][k][1]));
	cout << ans << endl;
	return 0;
}