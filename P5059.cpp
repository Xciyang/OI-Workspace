#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
long long n, P;
long long mul(long long a, long long b) {
	long long res= 0;
	while(b) {
		if(b & 1) res= (res + a) % P;
		a= (a + a) % P, b>>= 1;
	}
	return res;
}
struct MAT {
	int r, c;
	long long a[1 << 3][1 << 3];
	inline MAT operator*(const MAT &m2) const {
		MAT res;
		memset(&res, 0, sizeof(res));
		res.r= r, res.c= m2.c;
		for(int i= 0; i < r; i++) {
			for(int j= 0; j < c; j++) {
				for(int k= 0; k < m2.c; k++) {
					res.a[i][k]= (res.a[i][k] + mul(a[i][j], m2.a[j][k])) % P;
				}
			}
		}
		return res;
	}
} base, dw;
inline long long qpow(long long a, long long b) {
	long long res= 1;
	while(b) {
		if(b & 1) res= mul(res, a);
		a= mul(a, a), b>>= 1;
	}
	return res;
}
inline MAT qpow(MAT a, long long b) {
	MAT res= a;
	--b;
	while(b) {
		if(b & 1) res= res * a;
		a= a * a, b>>= 1;
	}
	return res;
}
int main() {
	cin >> n >> P;
	++n;
	base.r= base.c= 2;
	base.a[0][1]= 1;
	base.a[1][0]= base.a[0][0]= 1;
	dw.r= 1, dw.c= 2;
	dw.a[0][0]= 1;
	MAT p= qpow(base, n);
	dw= dw * p;
	long long ans= ((dw.a[0][0] + dw.a[0][1] - n - 1) % P + P) % P;
	cout << qpow(ans, n) << endl;
	return 0;
}