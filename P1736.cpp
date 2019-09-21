#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m;
int f1[2505][2505], f2[2505][2505], f[2505][2505], a[2505][2505], ans;
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++)
		for(int j= 1; j <= m; j++) cin >> a[i][j];
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) {
			f1[i][j]= f1[i][j - 1] + 1, f2[i][j]= f2[i - 1][j] + 1;
			if(a[i][j - 1]) f1[i][j]= 1;
			if(a[i - 1][j]) f2[i][j]= 1;
		}
	}
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) {
			if(a[i][j]) f[i][j]= min(f[i - 1][j - 1] + 1, min(f1[i][j], f2[i][j]));
			ans= max(ans, f[i][j]);
		}
	}
	memset(f1, 0, sizeof(f1)), memset(f2, 0, sizeof(f2)), memset(f, 0, sizeof(f));
	for(int i= 1; i <= n; i++) {
		for(int j= m; j; j--) {
			f1[i][j]= f1[i][j + 1] + 1, f2[i][j]= f2[i - 1][j] + 1;
			if(a[i][j + 1]) f1[i][j]= 1;
			if(a[i - 1][j]) f2[i][j]= 1;
		}
	}
	for(int i= 1; i <= n; i++) {
		for(int j= m; j; j--) {
			if(a[i][j]) f[i][j]= min(f[i - 1][j + 1] + 1, min(f1[i][j], f2[i][j]));
			ans= max(ans, f[i][j]);
		}
	}
	cout << ans << endl;
	return 0;
}