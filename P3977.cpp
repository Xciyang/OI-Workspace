#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m, p, k, M, c[1 << 7];
int gj[4][8];
struct MAT {
	unsigned int r, c, a[70][70];
	MAT operator*(const MAT &m2) const {
		MAT res;
		memset(&res, 0, sizeof(res));
		res.r= r, res.c= m2.c;
		for(int i= 0; i <= r; i++)
			for(int j= 0; j <= c; j++)
				for(int k= 0; k <= m2.c; k++) res.a[i][k]+= a[i][j] * m2.a[j][k];
		return res;
	}
} base, dw;
void init() {
	base.r= base.c= M - 1;
	for(int i= 0; i < M; i++) {
		for(int j= 1, l; j <= m; j++) {
			if((1 << (j - 1)) & i) {
				for(l= 1; l <= p; l++) {
					if(j - k + l < 1 || k == l) continue;
					if(((1 << (j - k + l - 1)) & i) && gj[2][l]) break;
				}
				if(l != p + 1) {
					c[i]= 1;
					break;
				}
			}
		}
	}
	for(int i= 0; i < M; i++) {
		if(c[i]) continue;
		for(int j= 0, flag; j < M; j++) {
			if(c[j]) continue;
			flag= 1;
			for(int l= 1, l2; l <= m; l++) {
				if((1 << (l - 1)) & i) {
					for(l2= 1; l2 <= p; l2++) {
						if(l - k + l2 < 1) continue;
						if(((1 << (l - k + l2 - 1)) & j) && gj[3][l2]) break;
					}
					if(l2 != p + 1) {
						flag= 0;
						break;
					}
				}
			}
			if(!flag) continue;
			for(int l= 1, l2; l <= m; l++) {
				if((1 << (l - 1)) & j) {
					for(l2= 1; l2 <= p; l2++) {
						if(l - k + l2 < 1) continue;
						if(((1 << (l - k + l2 - 1)) & i) && gj[1][l2]) break;
					}
					if(l2 != p + 1) {
						flag= 0;
						break;
					}
				}
			}
			if(flag) {
				// for(int l= m; l; l--) cout << ((i >> (l - 1)) & 1);
				// cout << endl;
				// for(int l= m; l; l--) cout << ((j >> (l - 1)) & 1);
				// cout << endl << endl;
				base.a[i][j]= 1;
			}
		}
	}
	return;
}

inline MAT qpow(MAT a, int b) {
	MAT res= a;
	--b;
	while(b) {
		if(b & 1) res= res * a;
		a= a * a, b>>= 1;
	}
	return res;
}
signed main() {
	cin >> n >> m;
	M= (1 << m);
	cin >> p >> k;
	++k;
	for(int i= 1; i <= 3; i++)
		for(int j= 1; j <= p; j++) cin >> gj[i][j];
	init();
	// for(int i= 0; i < M; i++) {
	// 	for(int j= 0; j < M; j++) cout << base.a[i][j] << ' ';
	// 	cout << endl;
	// }
	MAT p= qpow(base, n - 1);
	unsigned int ans= 0;
	dw.r= 0, dw.c= M - 1;
	for(int i= 0; i < M; i++) dw.a[0][i]= 1;
	dw= dw * p;
	for(int i= 0; i < M; i++) ans+= dw.a[0][i];
	// for(int i= 0; i < M; i++) {
	// 	for(int j= 0; j < M; j++) cout << p.a[i][j] << ' ', ans+= p.a[i][j];
	// 	cout << endl;
	// }
	cout << ans << endl;
	return 0;
}