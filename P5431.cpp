#include <iostream>
#include <stdio.h>
using namespace std;
char buf[(int)1e8], *ss= buf;
inline int init() {
	buf[fread(buf, 1, (int)1e8 - 1, stdin)]= '\n';
	fclose(stdin);
	return 0;
}
const int __START__= init();
inline int read() {
	int d= 0;
	while(!isdigit(*ss)) ++ss;
	while(isdigit(*ss)) d= d * 10 + (*ss++ ^ '0');
	return d;
}
int n, p, k, nk, a[5000006], qsum[5000006], hsum[5000006], tot;
inline int qpow(int a, int b) {
	int ans= 1;
	while(b) {
		if(b & 1) ans= (long long)ans * a % p;
		a= (long long)a * a % p;
		b>>= 1;
	}
	return ans;
}
signed main() {
	n= read(), p= read(), nk= k= read();
	qsum[0]= 1, hsum[n + 1]= 1;
	for(int i= 1; i <= n; i++) a[i]= read(), qsum[i]= (long long)qsum[i - 1] * a[i] % p;
	for(int i= n; i; i--) hsum[i]= (long long)hsum[i + 1] * a[i] % p;
	for(int i= 1; i <= n; i++, nk= (long long)nk * k % p) tot= ((long long)tot + ((long long)nk * qsum[i - 1] % p) * hsum[i + 1] % p) % p;
	cout << (long long)tot * qpow(qsum[n], p - 2) % p << endl;
	return 0;
}