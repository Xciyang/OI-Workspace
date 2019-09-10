#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, k, s[1005][1005], sum1[1005][1005], f[1005][1005][2], anss[1005];
int main() {
	cin >> n >> k;
	for(int i= 1; i <= n; i++)
		for(int j= i + 1; j <= n; j++) cin >> s[i][j];
	for(int i= 1; i <= n; i++)
		for(int j= n; j; j--) sum1[i][j]= sum1[i - 1][j] + sum1[i][j + 1] - sum1[i - 1][j + 1] + s[i][j];
	for(int i= 1; i <= k; i++)
		for(int j= 1; j <= n; j++)
			for(int l= i - 1; l < j; l++)
				if(f[j][i][0] < f[l][i - 1][0] + sum1[j][j + 1] - sum1[l][j + 1]) f[j][i][0]= f[l][i - 1][0] + sum1[j][j + 1] - sum1[l][j + 1], f[j][i][1]= l;
	for(int i= 1; i <= n; i++)
		if(f[i][k][0] > f[anss[k]][k][0]) anss[k]= i;
	for(int i= anss[k], j= k; j; i= f[i][j][1], j--) anss[j]= i;
	for(int i= 1; i <= k; i++) cout << anss[i] << ' ';
	return 0;
}