#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
long long m, A, C, x0, n, g;
long long mul(long long a, long long b, long long p) {
	long long res= 0;
	while(b) {
		if(b & 1) res= (res + a) % p;
		a= (a + a) % p, b>>= 1;
	}
	return res;
}
struct MAT {
	long long r, c, a[4][4];
	MAT operator*(const MAT &m2) const {
		MAT res;
		memset(&res, 0, sizeof(res));
		res.r= r, res.c= m2.c;
		for(long long i= 1; i <= r; i++) {
			for(long long j= 1; j <= c; j++) {
				for(long long k= 1; k <= m2.c; k++) {
					res.a[i][k]= (res.a[i][k] + mul(a[i][j], m2.a[j][k], m)) % m;
				}
			}
		}
		return res;
	}
} base, ans;
MAT qpow(MAT a, long long b) {
	MAT res= a;
	--b;
	while(b) {
		if(b & 1) res= res * a;
		a= a * a, b>>= 1;
	}
	return res;
}
int main() {
	cin >> m >> A >> C >> x0 >> n >> g;
	A= (A % m + m) % m;
	C= (C % m + m) % m;
	x0= (x0 % m + m) % m;
	base.r= base.c= 2;
	base.a[1][1]= A, base.a[2][1]= base.a[2][2]= 1;
	MAT res= qpow(base, n);
	ans.r= 1, ans.c= 2;
	ans.a[1][1]= x0, ans.a[1][2]= C;
	ans= ans * res;
	cout << (ans.a[1][1] % g + g) % g << endl;
	return 0;
}

// 100000000 1 1 1 1 100000000