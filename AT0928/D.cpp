#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
long long n, m, ans;
long long gcd(long long a, long long b) {
	return b ? gcd(b, a % b) : a;
}
int main() {
	cin >> n >> m;
	m= gcd(n, m);
	for(long long i= 2; i * i <= m; i++) {
		if(m % i == 0) {
			++ans;
			while(m % i == 0) m/= i;
		}
	}
	if(m > 1) ++ans;
	cout << ans + 1 << endl;
	return 0;
}