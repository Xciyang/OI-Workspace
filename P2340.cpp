#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int n, f[400005], ans;
struct NN {
	int q, z;
	inline int operator<(const NN &n2) const {
		return q > n2.q;
	}
} ns[405];
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> ns[i].q >> ns[i].z;
	sort(ns + 1, ns + n + 1);
	memset(f, ~0x3f, sizeof(f));
	f[0]= 0;
	for(int i= 1; i <= n; i++) {
		if(ns[i].q < 0)
			for(int j= 0; j <= 400000 + ns[i].q; j++) f[j]= max(f[j], f[j - ns[i].q] + ns[i].z);
		else
			for(int j= 400000; j >= ns[i].q; j--) f[j]= max(f[j], f[j - ns[i].q] + ns[i].z);
	}
	for(int i= 0; i <= 400000; i++)
		if(f[i] >= 0) ans= max(ans, i + f[i]);
	cout << ans << endl;
	return 0;
}