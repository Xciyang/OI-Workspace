#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <algorithm>
#define file(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)
using namespace std;
template < typename T >
inline void read(T &e) {
	e= 0;
	T f= 1;
	char ch= getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') e= e * 10 + ch - '0', ch= getchar();
	e*= f;
	return;
}
template < typename T >
inline int put(const T &e) {
	if(e < 0) return putchar('-'), put(-e);
	if(e > 9) put(e / 10);
	return putchar('0' + e % 10);
}
#define MAXSHAI 10000000
int n, phi[MAXSHAI + 5], inss[MAXSHAI + 5], pr[MAXSHAI + 5], pcnt;
inline int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
void shai() {
	phi[1]= inss[1]= 1;
	for(int i= 2; i <= MAXSHAI; i++) {
		if(!inss[i]) phi[i]= i - 1, pr[++pcnt]= i;
		for(int j= 1; j <= pcnt && pr[j] * i <= MAXSHAI; j++) {
			inss[pr[j] * i]= 1;
			if(gcd(pr[j], i) == 1)
				phi[pr[j] * i]= phi[pr[j]] * phi[i];
			else
				phi[pr[j] * i]= pr[j] * phi[i];
			if(i % pr[j] == 0) break;
		}
	}
	return;
}
int main() {
    file("phi");
	read(n), shai();
	int i;
	for(i= 1; i <= MAXSHAI; i++) {
		if(phi[i] == n) {
			cout << i << endl;
			break;
		}
	}
	if(i == MAXSHAI + 1) cout << -1 << endl;
	return 0;
}