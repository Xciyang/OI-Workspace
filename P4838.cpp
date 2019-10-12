#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int m;
long long n;
struct MAT {
	struct ARRAY {
		long long a[4];
		long long &operator[](const int &i) {
			return a[i];
		}
		long long operator[](const int &i) const {
			return a[i];
		}
	} a[4];
	ARRAY &operator[](const int &i) {
		return a[i];
	}
	ARRAY operator[](const int &i) const {
		return a[i];
	}
	MAT operator*(const MAT &m2) const {
		MAT r;
		memset(&r, 0, sizeof(r));
		for(int i= 0; i < 3; i++) {
			for(int j= 0; j < 3; j++) {
				for(int k= 0; k < 4; k++) {
					r[i][k]= (r[i][k] + a[i][j] * m2[j][k]) % 19260817;
				}
			}
		}
		return r;
	}
} base, ans, nbase, res;
void qpow() {
	nbase= base, res= ans;
	while(n) {
		if(n & 1) res= res * nbase;
		nbase= nbase * nbase, n>>= 1;
	}
	return;
}
inline long long qpow(long long a, long long b) {
	long long r= 1;
	while(b) {
		if(b & 1) r= r * a % 19260817;
		a= a * a % 19260817, b>>= 1;
	}
	return r;
}
int main() {
	base[0][0]= base[0][1]= base[0][2]= base[1][0]= base[2][1]= 1;
	ans[0][0]= ans[0][1]= 1;
	cin >> m;
	while(m--) {
		cin >> n;
		qpow();
		cout << (res[0][0] + res[0][1] + res[0][2]) * qpow(2, 19260815) % 19260817 << endl;
	}
	return 0;
}