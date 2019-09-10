#include <iostream>
#include <stdio.h>
#define int long long
using namespace std;
int n, ans;
int phi(int x) {
	int res= x;
	for(int i= 2; i * i <= x; i++) {
		if(x % i == 0) res= res / i * (i - 1);
		while(x % i == 0) x/= i;
	}
	if(x > 1) res= res / x * (x - 1);
	return res;
}
signed main() {
	cin >> n;
	for(int i= 1; i * i <= n; i++)
		if(n % i == 0) ans+= (i * i == n ? i * phi(i) : (n / i) * phi(i) + i * phi(n / i));
	cout << ans << endl;
	return 0;
}