#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, f[3005][3005], a[3005];
int main() {
	cin >> n;
	memset(f, 0x3f, sizeof(f));
	for(int i= 1; i <= n; i++) {
		cin >> a[i];
		f[i][i]= 0;
	}
	for(int i= 1; i < n; i++) f[i][i + 1]= (a[i] != a[i + 1]);
	for(int l= 3; l <= n; l++) {
		for(int i= 1, j= i + l - 1; j <= n; i++, j++) {
			if(a[i] != a[j])
				f[i][j]= min(f[i + 1][j - 1], min(f[i][j - 1], f[i + 1][j])) + 1;
			else
				f[i][j]= f[i + 1][j - 1];
		}
	}
	cout << f[1][n] << endl;
	return 0;
}