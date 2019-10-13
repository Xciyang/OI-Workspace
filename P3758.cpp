#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m, tmpx, tmpy;
int t;
struct MAT {
	int r, c, a[40][40];
	inline MAT operator*(const MAT &m2) const {
		MAT res;
		memset(&res, 0, sizeof(res));
		res.r= r, res.c= m2.c;
		for(int i= 1; i <= r; i++) {
			for(int j= 1; j <= c; j++) {
				for(int k= 1; k <= m2.c; k++) {
					res.a[i][k]= (res.a[i][k] + a[i][j] * m2.a[j][k]) % 2017;
				}
			}
		}
		return res;
	}
} base, ans;
MAT qpow(MAT a, int b) {
	MAT res= a;
	--b;
	while(b) {
		if(b & 1) res= res * a;
		a= a * a, b>>= 1;
	}
	return res;
}
int main() {
	cin >> n >> m;
	base.r= n + 1, base.c= n + 1;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy;
		base.a[tmpx][tmpy]= base.a[tmpy][tmpx]= 1;
	}
	for(int i= 1; i <= n + 1; i++) base.a[i][n + 1]= base.a[i][i]= 1;
	cin >> t;
	MAT p= qpow(base, t);
	int ans= 0;
	for(int i= 1; i <= n + 1; i++) ans= (ans + p.a[1][i]) % 2017;
	cout << ans<< endl;
	return 0;
}