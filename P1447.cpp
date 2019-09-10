#include <iostream>
#include <stdio.h>
using namespace std;
int n, m;
long long ans, f[100005];
int main() {
	cin >> n >> m;
	if(n > m) swap(n, m);
	for(int i= n; i; i--) {
		f[i]= (long long)(m / i) * (n / i);
		for(int j= i + i; j <= n; j+= i) f[i]-= f[j];
		ans+= (i + i - 1) * f[i];
	}
	cout << ans << endl;
	return 0;
}