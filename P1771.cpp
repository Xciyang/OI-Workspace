#include <iostream>
#include <stdio.h>
using namespace std;
int k;
long long x;
inline long long qpow(long long a, long long b, long long p) {
	if(!a) return 0;
	long long ans= 1;
	while(b) {
		if(b & 1) ans= ans * a % p;
		a= a * a % p, b>>= 1;
	}
	return ans;
}
long long f[105][1005];
int main() {
	cin >> k >> x;
	x= qpow(x % 1000, x % 1000, 1000);
	for(int i= 1; i <= x; i++) f[1][i]= 1;
	for(int i= 2; i <= k; i++)
		for(int j= 1; j < x; j++)
			for(int k= x; k > j; k--) f[i][k]+= f[i - 1][k - j];
	cout << f[k][x] << endl;
	return 0;
}