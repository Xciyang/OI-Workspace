#include <iostream>
#include <stdio.h>
#include <map>
using namespace std;
int n, p, c, a[33], ans;
map< int, int > cnt;
inline int qpow(int x, int y) {
	int ans= 1;
	while(y) {
		if(y & 1) ans= (long long)ans * x % p;
		x= (long long)x * x % p, y>>= 1;
	}
	return ans;
}
void dfs(int nown, int l) {
	if(nown == n / 2) {
		++cnt[l], ++cnt[(long long)l * a[nown] % p];
		return;
	}
	if(nown == n) {
		ans= ((long long)ans + cnt[(long long)c * qpow(a[nown] * l, p - 2) % p]) % 1000000007;
		ans= ((long long)ans + cnt[(long long)c * qpow(l, p - 2) % p]) % 1000000007;
		return;
	}
	dfs(nown + 1, l);
	dfs(nown + 1, (long long)l * a[nown] % p);
	return;
}
int main() {
	cin >> n >> p >> c;
	for(int i= 1; i <= n; i++) cin >> a[i];
	if(c >= p) {
		printf("0\n");
		return 0;
	}
	dfs(1, 1), dfs(n / 2 + 1, 1);
	printf("%d\n", (ans - (c == 1) + 1000000007) % 1000000007);
	return 0;
}