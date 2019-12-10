#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, gcdnm, nc, ans, w[256];
char df[10000007], my[10000007];
char JSB[4]= "JSB", kz[4]= "SBJ";
inline int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
int main() {
	scanf("%d%s%d", &n, df + 1, &m);
	gcdnm= gcd(n, m), nc= n / gcdnm;
	for(int i= 1; i <= gcdnm; i++) {
		w['J']= w['S']= w['B']= 0;
		for(int j= 1; j <= nc; j++) ++w[df[(gcdnm * (j - 1) + i) % n + 1]];
		int tmpi= -1;
		for(int j= 0; j < 3; j++)
			if(w[JSB[j]] - w[kz[j]] > tmpi) tmpi= w[JSB[j]] - w[kz[j]], my[i]= kz[j];
		ans+= tmpi;
	}
	for(int i= 1; i <= m; i++) putchar(my[(i - 1) % gcdnm + 1]);
	putchar('\n');
	return 0;
}