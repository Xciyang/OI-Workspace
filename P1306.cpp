#include <iostream>
#include <stdio.h>
using namespace std;
#define int long long 
inline int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
int n, m;
struct MAT {
	int r[3][3];
} a, b;
MAT mul(const MAT &m1, const MAT &m2) {
	MAT c;
	for(int i= 1; i <= 2; i++)
		for(int j= 1; j <= 2; j++) c.r[i][j]= 0;

	for(int i= 1; i <= 2; i++)
		for(int j= 1; j <= 2; j++)
			for(int k= 1; k <= 2; k++) c.r[i][k]= (c.r[i][k] + m1.r[i][j] * m2.r[j][k]) % 100000000;
	return c;
}
signed main() {
	cin >> n >> m;
    n= gcd(n, m);
	if(n <= 2) cout << 1 << endl;
	a.r[1][1]= a.r[1][2]= a.r[2][1]= 1;
	for(int i= 1; i <= 2; i++) b.r[i][i]= 1;
	while(n) {
		if(n & 1) b = mul(b, a);
        a= mul(a, a);
        n>>= 1;
	}
    cout << b.r[2][1] << endl;
	return 0;
}