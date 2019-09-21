#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, a[1005], b[1005], c[1005], f[2][8000], sum;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i] >> b[i], c[i]= a[i] - b[i], sum+= a[i] + b[i];
	memset(f, 0x3f, sizeof(f));
	f[0][0]= 0;
	for(int i= 1; i <= n; i++) {
		for(int j= 0; j <= sum; j++) f[i & 1][j]= 0x3f3f3f3f;
		for(int j= sum; j >= a[i]; j--) f[i & 1][j]= f[(i & 1) ^ 1][j - a[i]];
		for(int j= sum; j >= b[i]; j--) f[i & 1][j]= min(f[i & 1][j], f[(i & 1) ^ 1][j - b[i]] + 1);
	}
	int res= 0x3f3f3f3f, sum1= sum / 2, sum2= sum1 + sum % 2;
	for(int i= 0; i < sum; i++) {
		if(sum1 + i > n && sum2 - i < 1) break;
		res= min(f[n & 1][sum1 + i], f[n & 1][sum2 - i]);
		if(f[n & 1][sum1 + i] != 0x3f3f3f3f || f[n & 1][sum2 - i] != 0x3f3f3f3f) break;
	}
	cout << res << endl;
	return 0;
}