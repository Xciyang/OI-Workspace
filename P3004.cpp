#include <iostream>
#include <stdio.h>
using namespace std;
int n, f[5005], sum[5005];
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> f[i], sum[i]= sum[i - 1] + f[i];
	for(int l= 2; l <= n; l++)
		for(int i= 1, j= i + l - 1; j <= n; i++, j++) f[i]= sum[j] - sum[i - 1] - min(f[i], f[i + 1]);
	cout << f[1] << endl;
	return 0;
}