#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;
long long n, m, a, b, c, d;
long long p= 1000000007;
struct MAT {
	int r, c;
	long long a[4][4];
	inline MAT operator*(const MAT &m2) const {
		MAT res;
		memset(&res, 0, sizeof(res));
		res.r= r, res.c= m2.c;
		for(int i= 1; i <= r; i++) {
			for(int j= 1; j <= c; j++) {
				for(int k= 1; k <= m2.c; k++) res.a[i][k]= (res.a[i][k] + a[i][j] * m2.a[j][k]) % p;
			}
		}
		return res;
	}
} base1, base2, dw;
inline MAT qpow(MAT a, int b) {
	MAT res= a;
	--b;
	while(b) {
		if(b & 1) res= res * a;
		a= a * a, b>>= 1;
	}
	return res;
}
int main() {
	string stn, stm;
	cin >> stn >> stm;
	cin >> a >> b >> c >> d;
	int Mod= p - 1;
	if(a == 1) Mod= p;
	for(int i= 0; i < stn.size(); i++) n= (n * 10 + stn[i] - '0') % Mod;
	for(int i= 0; i < stm.size(); i++) m= (m * 10 + stm[i] - '0') % Mod;
	base1.r= base1.c= 2;
	base1.a[1][1]= a, base1.a[2][1]= b, base1.a[2][2]= 1;
	MAT res1= qpow(base1, m - 1);
	base2.r= base2.c= 2;
	base2.a[1][1]= c, base2.a[2][1]= d, base2.a[2][2]= 1;
	base2= res1 * base2;
	MAT res2= qpow(base2, n - 1);
	res1= res2 * res1;
	dw.r= 1, dw.c= 2;
	dw.a[1][1]= 1, dw.a[1][2]= 1;
	res1= dw * res1;
	cout << res1.a[1][1] << endl;
	return 0;
}

/*
3 3 2 3 2 4
3 1000000009 1 3 2 6
*/