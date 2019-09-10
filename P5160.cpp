#include <iostream>
#include <stdio.h>
#define int long long
using namespace std;
int t, mod, n, m, fac[19491005];
inline int qpow(int a, int b) {
	int res= 1;
	while(b) {
		if(b & 1) res= res * a % mod;
		a= a * a % mod, b>>= 1;
	}
	return res;
}
inline void init() {
	fac[0]= 1;
	for(int i= 1; i <= mod; i++) fac[i]= fac[i - 1] * (i % mod) % mod;
	return;
}
inline int C(int a, int b) {
	if(a < b) return 0;
	return fac[a] * qpow(fac[a - b], mod - 2) % mod * qpow(fac[b], mod - 2) % mod;
}
inline int lucas(int a, int b) {
	if(a < b) return 0;
	if(!a) return 1;
	return C(a % mod, b % mod) * lucas(a / mod, b / mod) % mod;
}
signed main() {
	cin >> t, mod= 19491001, init();
	while(t--) {
		cin >> n >> m;
		cout << lucas(m + n, m) << endl;
	}
	return 0;
}