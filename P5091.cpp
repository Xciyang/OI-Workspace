#include <iostream>
#include <stdio.h>
using namespace std;
int a, m, b, phim, flag;
int eular(int x) {
	int ans= x;
	for(int i= 2; i * i <= x; ++i) {
		if(x % i == 0) {
			ans-= ans / i;
			while(x % i == 0) x/= i;
		}
	}
	if(x > 1) ans-= ans / x;
	return ans;
}
int qpow(int x, int e, int p) {
	int ans= 1;
	while(e) {
		if(e & 1) ans= (long long)ans * x % p;
		x= (long long)x * x % p;
		e>>= 1;
	}
	return ans;
}
int main() {
	cin >> a >> m, phim= eular(m);
	char ch= getchar();
	while(ch < '0' || ch > '9') ch= getchar();
	while(ch >= '0' && ch <= '9') {
		b= b * 10 + ch - '0';
		if(b >= phim) {
			flag= 1;
			b%= phim;
		}
        ch= getchar();
	}
	if(flag) b+= phim;
	cout << qpow(a, b, m) << endl;
	return 0;
}