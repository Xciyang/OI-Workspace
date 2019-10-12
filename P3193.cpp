// #include <iostream>
// #include <stdio.h>
// #include <string.h>
// using namespace std;
// char tmpc[25];
// int n, m, K, tmpx;
// struct MAT {
// 	int r, c, a[205][205];
// 	MAT operator*(const MAT &m2) const {
// 		MAT res;
// 		memset(&res, 0, sizeof(res));
// 		res.r= r, res.c= m2.c;
// 		for(int i= 1; i <= r; i++) {
// 			for(int j= 1; j <= c; j++) {
// 				for(int k= 1; k <= m2.c; k++) {
// 					res.a[i][k]= (res.a[i][k] + a[i][j] * m2.a[j][k]) % K;
// 				}
// 			}
// 		}
// 		return res;
// 	}
// } base, ans;
// inline int judge(char *s, char *e, int len) {
// 	for(int i= 0; i < len; i++)
// 		if(s[i] != e[i]) return 0;
// 	return 1;
// }
// inline int query(int x, char c) {
// 	return x * 10 + c - '0' + 1;
// }
// inline MAT qpow(MAT a, int b) {
// 	MAT res= a;
// 	--b;
// 	while(b) {
// 		if(b & 1) res= res * a;
// 		a= a * a, b>>= 1;
// 	}
// 	return res;
// }
// inline int qpow(int a, int b) {
// 	int res= 1;
// 	while(b) {
// 		if(b & 1) res= 1ll * res * a % K;
// 		a= 1ll * a * a % K, b>>= 1;
// 	}
// 	return res;
// }
// int F[1005][1005][15], sum;
// int main() {
// 	cin >> n >> m >> K >> (tmpc + 1);
// 	base.r= (m + 1) * 10, base.c= (m + 1) * 10;
// 	for(int i= '0'; i <= '9'; i++) {
// 		for(int j= '0'; j <= '9'; j++) {
// 			++base.a[query(0, i)][query((j == tmpc[1]), j)];
// 			++base.a[query(m, i)][query(m, j)];
// 		}
// 	}
// 	for(int i= 2; i <= m; i++) {
// 		for(int j= '0'; j <= '9'; j++) {
// 			if(tmpc[i] == j) {
// 				++base.a[query(i - 1, tmpc[i - 1])][query(i, j)];
// 				continue;
// 			}
// 			for(int k= i - 1; k >= 0; k--) {
// 				if((judge(tmpc + 1, tmpc + i - k + 1, k - 1) && tmpc[k] == j) || !k) {
// 					++base.a[query(i - 1, tmpc[i - 1])][query(k, j)];
// 					break;
// 				}
// 			}
// 		}
// 	}
// 	F[0][0][0]= 1;
// 	for(int i= 1; i <= n; i++) {
// 		for(int j= 0; j <= m; j++) {
// 			for(int k= 0; k <= m; k++) {
// 				for(int c= 0; c <= 9; c++) {
// 					for(int c2= 0; c2 <= 9; c2++) {
// 						F[i][j][c]= (F[i][j][c] + 1LL * F[i - 1][k][c2] * base.a[query(k, c2 + '0')][query(j, c + '0')]) % K;
// 					}
// 				}
// 			}
// 		}
// 	}
// 	for(int i= 0; i <= 9; i++) sum= (sum + F[n][m][i]) % K;
// 	// MAT p= qpow(base, n);
// 	// for(int j= '0'; j <= '9'; j++) sum= (sum + p.a[query(0, '0')][query(m, j)]) % K;
// 	cout << (qpow(10, n) - sum + K) % K << endl;

// 	return 0;
// }

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
char tmpc[25];
int n, m, K, tmpx, tmp[250][250];
struct MAT {
	int r, c, a[250][250];
	MAT operator*(const MAT &m2) const {
		MAT res;
		res.r= r, res.c= m2.c;
		for(int i= 0; i <= res.r; i++)
			for(int j= 0; j <= res.c; j++) res.a[i][j]= 0;
		for(int i= 0; i <= r; i++)
			for(int j= 0; j <= c; j++)
				for(int k= 0; k <= m2.c; k++) res.a[i][k]= (res.a[i][k] + 1ll * a[i][j] * m2.a[j][k]) % K;
		return res;
	}
	void operator*=(const MAT &m2) {
		for(int i= 0; i <= r; i++)
			for(int j= 0; j <= m2.c; j++) tmp[i][j]= 0;
		for(int i= 0; i <= r; i++)
			for(int j= 0; j <= c; j++)
				for(int k= 0; k <= m2.c; k++) tmp[i][k]= (tmp[i][k] + 1ll * a[i][j] * m2.a[j][k]) % K;
		c= m2.c;
		for(int i= 0; i <= r; i++)
			for(int j= 0; j <= c; j++) a[i][j]= tmp[i][j];
		return;
	}
} base;
inline int judge(char *s, char *e, int len) {
	for(int i= 0; i < len; i++)
		if(s[i] != e[i]) return 0;
	return 1;
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
inline int qpow(int a, int b) {
	int ans= 1;
	while(b) {
		if(b & 1) ans= 1ll * ans * a % K;
		a= 1ll * a * a % K, b>>= 1;
	}
	return ans;
}
int sum;
int main() {
	cin >> n >> m >> K >> (tmpc + 1);
	base.r= m, base.c= m;
	base.a[0][0]= 9;
	base.a[m][m]= 10;
	base.a[0][1]= 1;
	for(int i= 2; i <= m; i++) {
		for(int j= '0'; j <= '9'; j++) {
			if(i > 1 && tmpc[i] == j) {
				++base.a[i - 1][i];
				continue;
			}
			for(int k= i - 1; k >= 0; k--) {
				if((judge(tmpc + 1, tmpc + i - k + 1, k - 1) && tmpc[k] == j) || !k) {
					++base.a[i - 1][k];
					break;
				}
			}
		}
	}
	MAT p= qpow(base, n);
	cout << (qpow(10, n) - p.a[0][m] + K) % K << endl;
	return 0;
}