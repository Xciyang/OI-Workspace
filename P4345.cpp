#include <iostream>
#include <stdio.h>
using namespace std;
#define int long long
int t, c[2400][2400], f[2400][2400], n, k;
int C(int a, int b) {
	if(!b || a == b) return 1;
	if(a < b) return 0;
	return c[a % 2333][b % 2333] * C(a / 2333, b / 2333) % 2333;
}
int F(int a, int b) {
	if(b < 0) return 0 ;
	if(!a || !b) return 1;
	if(a < 2333 && b < 2333) return f[a][b];
	return (F(a % 2333, 2332) * F(a / 2333, b / 2333 - 1) % 2333 + C(a / 2333, b / 2333) * F(a % 2333, b % 2333) % 2333) % 2333;
}
signed main() {
	for(int i= 0; i < 2400; i++) f[i][0]= c[i][0]= c[i][i]= 1;
	for(int i= 1; i < 2400; i++)
		for(int j= 1; j < i; j++) c[i][j]= (c[i - 1][j] + c[i - 1][j - 1]) % 2333;
	for(int i= 1; i < 2400; i++)
		for(int j= 1; j < 2400; j++) f[i][j]= (f[i][j - 1] + c[i][j]) % 2333;
	cin >> t;
	while(t--) {
		cin >> n >> k;
		cout << F(n, k) << endl;
	}
	return 0;
}