#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int n, m, k, w[1005], a[105], b[105], f[100005], ans, F[2][100005];
int main() {
	cin >> n >> m >> k;
	for(int i= 0; i <= k; i++) cin >> w[i];
	memset(f, ~0x3f, sizeof(f));
	f[0]= 0;
	for(int i= 1; i <= m; i++) {
		cin >> a[i] >> b[i];
		for(int j= a[i]; j <= 100000; j++) f[j]= max(f[j], f[j - a[i]] + b[i]);
	}
	memset(F, ~0x3f, sizeof(F));
	F[0][0]= 0;
	for(int i= 1; i <= n; i++) {
		for(int j= 0; j <= 1000; j++) {
            for(int k= j; j <= )
		}
	}
	return 0;
}