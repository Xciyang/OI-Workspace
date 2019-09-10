#include <iostream>
#include <stdio.h>
using namespace std;
long long n, g, frac[40000], mods[5]= {0, 2, 3, 4679, 35617}, res[5], ans;
void init(long long p) {
    frac[0]= 1;
	for(int i= 1; i <= p; i++) frac[i]= frac[i - 1] * i % p;
    return;
}
inline long long qpow(long long a, long long b, long long p) {
	if(!a) return 0;
	int ans= 1;
	while(b) {
		if(b & 1) ans= ans * a % p;
		a= a * a % p, b>>= 1;
	}
	return ans;
}
inline long long C(long long x, long long y, long long p) {
	if(x < y) return 0;
	return frac[x] * qpow(frac[y], p - 2, p) % p * qpow(frac[x - y], p - 2, p) % p;
}
long long lucas(long long x, long long y, long long p) {
	if(x < y) return 0;
	if(!x) return 1;
	return lucas(x / p, y / p, p) * C(x % p, y % p, p) % p;
}
int main() {
	cin >> n >> g;
	if(g % 999911659 == 0) return cout << 0 << endl, 0;
	for(int i= 1; i < 5; i++) {
		init(mods[i]);
		for(int j= 1; j * j <= n; j++) {
			if(n % j == 0) {
				res[i]= (res[i] + lucas(n, j, mods[i])) % mods[i];
				if(j * j != n) res[i]= (res[i] + lucas(n, n / j, mods[i])) % mods[i];
			}
		}
	}
	for(int i= 1; i < 5; i++) ans= (ans + res[i] * (999911658 / mods[i]) % 999911658 * qpow(999911658 / mods[i], mods[i] - 2, mods[i])) % 999911658;
    cout << qpow(g, ans, 999911659) << endl;
	return 0;
}