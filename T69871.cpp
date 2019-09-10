#include <iostream>
#include <stdio.h>
#define int long long
using namespace std;
int t, p, ans[3], A, B, C, gcda[101][101];
inline int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
inline int qpow(int a, int b) {
	int res= 1;
	while(b) {
		if(b & 1) res= res * a % p;
		a= a * a % p, b>>= 1;
	}
	return res;
}
signed main() {
	scanf("%d%d", &t, &p);
	for(int i= 1; i <= 100; i++)
		for(int j= 1; j <= 100; j++) gcda[i][j]= gcd(i, j);
	while(t--) {
		scanf("%d%d%d", &A, &B, &C);
		ans[0]= ans[1]= ans[2]= 1;
		for(int i= 1, lcmij; i <= A; i++) {
			for(int j= 1; j <= B; j++) {
				lcmij= i * j / gcda[i][j];
				for(int k= 1; k <= C; k++) {
					ans[0]= ans[0] * lcmij / gcda[i][k] % p;
					ans[1]= ans[1] * qpow(lcmij / gcda[i][k], i * j * k % p) % p;
					ans[2]= ans[2] * qpow(lcmij / gcda[i][k], gcda[gcda[i][j]][k]) % p;
				}
			}
		}
		printf("%d %d %d\n", ans[0], ans[1], ans[2]);
	}
	return 0;
}