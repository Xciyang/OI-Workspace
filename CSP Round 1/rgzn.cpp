#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, gcdnm, nc, w[256];
char df[10000007], my[10000007];
char JSB[4]= "JSB", kz[4]= "SBJ", www[4]= "BJS";
inline int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
int main() {
	scanf("%d%s%d", &n, df + 1, &m);
	gcdnm= gcd(n, m), nc= n / gcdnm;
	for(int i= 1; i <= gcdnm; i++) {
		w['J']= w['S']= w['B']= 0;
		for(int j= 1; j <= nc; j++) ++w[df[(gcdnm * (j - 1) + i - 1) % n + 1]];
		int tmpi= ~0x3f3f3f3f;
		for(int j= 0; j < 3; j++)
			if(w[JSB[j]] - w[www[j]] > tmpi) tmpi= w[JSB[j]] - w[www[j]], my[i]= kz[j];
	}
	for(int i= 1; i <= m; i++) putchar(my[(i - 1) % gcdnm + 1]);
	putchar('\n');
	return 0;
}