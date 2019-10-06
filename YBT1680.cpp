#include <iostream>
#include <stdio.h>
using namespace std;
int t, n;
long long ans;
inline long long gcd(long long a, long long b) {
	return b ? gcd(b, a % b) : a;
}
int main() {
	cin >> t;
	while(t--) {
		cin >> n;
	}
	return 0;
}