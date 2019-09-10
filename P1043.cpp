#include <iostream>
#include <stdio.h>
#include <string.h>
#define int long long
using namespace std;
int n, m, a[100], psum[100], f1[200][200][20], f2[200][200][20];
inline int mod(int x) {
	return (x % 10 + 10) % 10;
}
signed main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) cin >> a[i], a[n + i]= a[i];
	for(int i= 1; i <= n * 2; i++) psum[i]= psum[i - 1] + a[i]; 
	for(int i= 2; i <= m; i++)
		for(int l= 1; l <= n * 2; l++)
			for(int r= l + i - 1; r <= n * 2; r++) f2[l][r][i]= 2147483647;
	for(int i= 1; i <= n * 2; i++)
		for(int j= i; j <= n * 2; j++) f1[i][j][1]= f2[i][j][1]= mod(psum[j] - psum[i - 1]);
	for(int i= 2; i <= m; i++)
		for(int l= 1; l <= n * 2; l++)
			for(int r= l + i - 1; r <= n * 2; r++)
				for(int k= l + i - 2; k < r; k++) f1[l][r][i]= max(f1[l][r][i], f1[l][k][i - 1] * mod(psum[r] - psum[k])), f2[l][r][i]= min(f2[l][r][i], f2[l][k][i - 1] * mod(psum[r] - psum[k]));
	int ans1= 0, ans2= 2147483647;
	for(int i= 1; i <= n; i++) ans1= max(ans1, f1[i][i + n - 1][m]), ans2= min(ans2, f2[i][i + n - 1][m]);
	cout << ans2 << endl << ans1 << endl;
	return 0;
}