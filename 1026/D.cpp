// #include <iostream>
// #include <stdio.h>
// using namespace std;
// int n, f[2005][2005], ans, f2[2005];
// const int mod= 998244353;
// int main() {
// 	for(int k= 1; k <= 10; k++) {
// 		n= k;
// 		++n;
// 		f[1][1]= f2[0]= 1;
// 		for(int i= 1; i <= n; i++) f2[i]= (1ll * f2[i - 1] * f2[i - 1] + 2) % mod;
// 		for(int i= 1; i <= n; i++) {
// 			for(int j= 1; j <= n; j++) {
// 				if(i == 1 && j == 1) continue;
// 				f[i][j]= ((long long)f[i - 1][j] + f[i][j - 1] + f[i - 1][j - 1]) % mod;
// 			}
// 		}
// 		ans= 0;
// 		for(int j= 1; j <= n; j++) ans= (ans + 1ll * f[j][j] * f2[j - 1]) % mod;
// 		cout << ans << endl;
// 	}

// 	return 0;
// }
#include <iostream>
#include <stdio.h>
using namespace std;
const long long mod= 998244353;
int n, f[1000006], ans, f2[1000006], frac[1000006];
inline long long qpow(long long a, long long b) {
	long long res= 1;
	while(b) {
		if(b & 1) res= res * a % mod;
		a= a * a % mod, b>>= 1;
	}
	return res;
}
int main() {
	cin >> n;
	f2[0]= frac[0]= 1;
	for(int i= 1; i <= n; i++) f2[i]= (1ll * f2[i - 1] * f2[i - 1] + 2) % mod;
	f[0]= 1, f[1]= 3;
	ans= (ans + f[0] * f2[0] + f[1] * f2[1]) % mod;
	for(int i= 2; i <= n; i++) {
		int res= 0;
		f[i]= ((3ll * (2 * i - 1) * f[i - 1] - 1ll * (i - 1) * f[i - 2]) % mod + mod) * qpow(i, mod - 2) % mod;
		ans= (ans + 1ll * f[i] * f2[i]) % mod;
	}
	cout << ans << endl;
	return 0;
}
/*



Sum_{k=0..n} C(n,k)*C(n+k,k)

C(N, M) = N! / M! / (N - M)!
*/

/*
1, 3, 13, 63, 321, 1683, 8989, 48639, 265729, 1462563, 8097453, 45046719, 251595969, 1409933619,
*/