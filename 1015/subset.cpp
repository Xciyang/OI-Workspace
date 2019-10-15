#include <iostream>
#include <stdio.h>
using namespace std;
int ans, wp[1000006];
long long n;
const int mod= 998244353;
inline long long gcd(long long a, long long b) {
	return b ? gcd(b, a % b) : a;
}
void dfs2(int lastt, long long bs) {
	if(bs == n && ++ans == mod) ans= 0;
	long long nxtbs;
	for(int i= lastt; i <= n; i++) {
		if(wp[i] || n % i) continue;
		wp[i]= 1, nxtbs= bs * i / gcd(i, bs);
		dfs2(i + 1, nxtbs), wp[i]= 0;
	}
	return;
}
void dfs(int lastt, long long bs, int gc) {
	if(gc == 1) {
		dfs2(lastt, bs);
		return;
	}
	long long nxtbs;
	for(int i= lastt, nxtgc; i <= n; i++) {
		if(wp[i] || n % i) continue;
		wp[i]= 1, nxtgc= gcd(i, gc), nxtbs= bs * i / gcd(i, bs);
		dfs(i + 1, nxtbs, nxtgc), wp[i]= 0;
	}
	return;
}
int main() {
	// for(int i= 1; i <= 100; i++) {
	// 	n= i, ans= 0;

	// 	// if(isPrim())
	// 	// 	ans= 1;
	// 	// else
	// 	dfs(1, 1, 0);

	// 	cout << i << ':' << ans << endl;
	// }
	cin >> n, ans= 0;

	// if(isPrim())
	// 	ans= 1;
	// else
	dfs(1, 1, 0);

	cout << ans << endl;

	return 0;
}