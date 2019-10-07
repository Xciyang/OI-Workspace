#include <iostream>
#include <stdio.h>
using namespace std;
int n, a[1005], f[1005][1005][2];
const int p= 19650827;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i], f[i][i][0]= 1;
	for(int k= 2; k <= n; k++) {
		for(int i= 1, j= k; j <= n; i++, j++) {
			if(a[i] < a[i + 1]) f[i][j][0]= (f[i][j][0] + f[i + 1][j][0]) % p;
			if(a[i] < a[j]) f[i][j][0]= (f[i][j][0] + f[i + 1][j][1]) % p;
			if(a[j] > a[j - 1]) f[i][j][1]= (f[i][j][1] + f[i][j - 1][1]) % p;
			if(a[j] > a[i]) f[i][j][1]= (f[i][j][1] + f[i][j - 1][0]) % p;
		}
	}
	cout << (f[1][n][0] + f[1][n][1]) % p << endl;
	return 0;
}