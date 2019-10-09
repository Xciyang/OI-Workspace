#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, ans, lcmnm, w[3];
char df[10000007], my[10000007];

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
signed main() {
	cin >> n >> (df + 1) >> m;
	lcmnm= n * m / gcd(n, m);
	for(int i= 1; i <= m; i++) {
		memset(w, 0, sizeof(w));
		for(int j= 1; j <= lcmnm / m; j++) ++w[chartoint(df[(m * (j - 1) + i) % n + 1])];
		int tmpi= -1;
		for(int j= 0; j < 3; j++)
			if(w[j] - w[kz(j)] > tmpi) tmpi= w[j] - w[kz(j)], my[i]= inttochar(kz(j));
		ans+= tmpi;
	}
	cout << my + 1 << endl;
	return 0;
}