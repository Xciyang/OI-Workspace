#include <iostream>
#include <stdio.h>
#include <string.h>
#define int long long
using namespace std;
int n, m;

struct MAT {
	int r, c, a[4][4];
	MAT operator*(const MAT &m2) const {
		MAT res;
		memset(&res, 0, sizeof(res));
		res.r= r, res.c= m2.c;
		for(int i= 1; i <= r; i++)
			for(int j= 1; j <= c; j++)
				for(int k= 1; k <= m2.c; k++) res.a[i][k]= (res.a[i][k] + 1ll * a[i][j] * m2.a[j][k]) % m;
		return res;
	}
} base, dw;
inline MAT qpow(MAT a, int b) {
	if(!b) {
		MAT res;
		memset(&res, 0, sizeof(res));
		return res;
	}
	MAT res= a;
	--b;
	while(b) {
		if(b & 1) res= res * a;
		a= a * a, b>>= 1;
	}
	return res;
}
int ans;
signed main() {
	cin >> n >> m;
	base.r= base.c= 3;
	base.a[2][1]= base.a[2][2]= base.a[3][1]= base.a[3][2]= base.a[3][3]= 1;
	dw.r= dw.c= 3;
	dw.a[1][1]= dw.a[2][2]= dw.a[3][3]= 1;
	int w= 10;
	while(w <= n) {
		base.a[1][1]= w % m;
		dw= dw * qpow(base, w - (w / 10));
		w*= 10;
	}
	base.a[1][1]= w % m;
	dw= dw * qpow(base, n - (w / 10) + 1);
	cout << dw.a[3][1] << endl;
	return 0;
}

// F[N] = F[N - 1] * 10^{lg^N + 1} + N

// +    F[N]  N   1
// F[N] 10^K  0   0
// N    1     1   0
// 1    1     1   1