#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, k, sum[1005];
double xb, f[1005][105];
char tmps[105];
int main() {
	cin >> n >> k;
	for(int i= 1; i <= n; i++) {
		cin >> tmps;
		sum[i]= sum[i - 1] + strlen(tmps);
	}
	xb= (double)sum[n] / k;
	for(int i= 1; i <= n; i++) f[i][1]= (sum[i] - sum[0] - xb) * (sum[i] - sum[0] - xb);
	for(int j= 2; j <= k; j++) {
		for(int i= 1; i <= n; i++) {
			f[i][j]= 1e9;
			for(int l= 1; l < i; l++) f[i][j]= min(f[i][j], f[l][j - 1] + ((double)sum[i] - sum[l] - xb) * (sum[i] - sum[l] - xb));
		}
	}
	printf("%.1lf\n", f[n][k] / k);
	return 0;
}