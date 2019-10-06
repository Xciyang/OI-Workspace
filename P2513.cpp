#include <iostream>
#include <stdio.h>
using namespace std;
int n, k, f[1005][1005], sum[1005][1005];
int main() {
	cin >> n >> k;
	for(int i= 1; i <= n; i++) {
		sum[i][0]= f[i][0]= 1;
		for(int j= 1; j <= k; j++) {
			f[i][j]= sum[i - 1][j];
			if(j - i >= 0) f[i][j]-= sum[i - 1][j - i];
            f[i][j]%= 10000;
			sum[i][j]= (sum[i][j - 1] + f[i][j] )% 10000;
		}
	}
	cout << (f[n][k] + 10000) % 10000<< endl;
	return 0;
}