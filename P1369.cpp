#include <iostream>
#include <stdio.h>
using namespace std;
int n, w[105][105], tmpx, tmpy, sum[105][105], bestans;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> tmpx >> tmpy, ++w[tmpx][tmpy];
	for(int i= 1; i <= 100; i++)
		for(int j= 1; j <= 100; j++) sum[i][j]= sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + w[i][j];
	for(int i= 1; i <= 100; i++) {
		for(int j= 1; j <= 100; j++) {
			for(int k= i + 1; k <= 100; k++) {
				for(int l= j + 1; l <= 100; l++) {
					int ans= sum[k][l] - sum[i - 1][l] - sum[k][j - 1] + sum[i - 1][j - 1];
					int ans2= sum[k - 1][l - 1] - sum[i][l - 1] - sum[k - 1][j] + sum[i][j];
					bestans= max(bestans, ans - ans2);
				}
			}
		}
	}
	cout << bestans << endl;
	return 0;
}