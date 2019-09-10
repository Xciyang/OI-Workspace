#include <iostream>
#include <stdio.h>
using namespace std;
int T, R, isnzhi[10000005], p[1000005], pcnt, inv[10000005], pf[1000005], pinv[1000005], frac[10000005], pos[10000005];
int m, n;
int main() {
	cin >> T >> R;
	isnzhi[1]= 1;
	for(int i= 2; i <= 10000000; i++) {
		if(!isnzhi[i]) p[++pcnt]= i;
		for(int j= 1; j <= pcnt && p[j] * i <= 10000000; j++) {
			isnzhi[p[j] * i]= 1;
			if(i % p[j] == 0) break;
		}
	}
	inv[1]= 1, pf[0]= 1, pinv[0]= 1, frac[0]= 1;
	for(int i= 2; i <= 10000000; i++) inv[i]= (long long)(R - R / i) * inv[R % i] % R;
	for(int i= 1; i <= pcnt; i++) pf[i]= (long long)pf[i - 1] * (p[i] - 1) % R;
	for(int i= 1; i <= pcnt; i++) pinv[i]= (p[i] == R ? pinv[i - 1] : (long long)pinv[i - 1] * inv[p[i] % R] % R);
	for(int i= 1; i <= 10000000; i++) frac[i]= (i == R ? frac[i - 1] : (long long)frac[i - 1] * i % R);
	for(int i= 2; i <= 10000000; i++) pos[i]= pos[i - 1] + (isnzhi[i] == 0);
	while(T--) {
		cin >> n >> m;
		if(n >= R && m < R)
			cout << 0 << endl;
		else
			cout << (long long)frac[n] * pf[pos[m]] % R * pinv[pos[m]] % R << endl;
	}
	return 0;
}