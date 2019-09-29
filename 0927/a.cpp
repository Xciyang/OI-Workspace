#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
using namespace std;
long long n;
long long qpow(long long a, long long b, long long p) {
	long long ans= 1;
	while(b) {
		if(b & 1) ans= ans * a % p;
		a= a * a % p, b>>= 1;
	}
	return ans;
}
const long long mod= 1e9 + 7;
int main() {
	cin >> n;
	if(n <= 4) {
		cout << n << endl;
		return 0;
	}
	cout << qpow(3, (n - 2) / 3, 1e9 + 7) * ((n - 2) % 3 + 2) % mod << endl;
	return 0;
}