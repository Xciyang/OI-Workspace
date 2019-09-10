#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, d[10004], f[10004][500];
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) cin >> d[i];
	for(int i= 1; i <= n; i++) {
		f[i][0]= f[i - 1][0];
		for(int j= 1; j <= m && j <= i; j++) f[i][j]= f[i - 1][j - 1] + d[i], f[i][0]= max(f[i][0], f[i - j][j]);
	}
	cout << f[n][0] << endl;
	return 0;
}