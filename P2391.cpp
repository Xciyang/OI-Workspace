#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, p, q, f[1000005], c[1000005];
inline int getf(int x) {
	return f[x] == x ? x : f[x]= getf(f[x]);
}
int main() {
	cin >> n >> m >> p >> q;
	for(int i= 1; i <= n; i++) f[i]= i;
	for(int i= m; i; i--) {
		int x= (1ll * i * p + q) % n + 1, y= (1ll * i * q + p) % n + 1;
		if(x > y) swap(x, y);
		for(int j= y; j >= x; j= getf(j)) {
			if(!c[j]) {
				c[j]= i;
				f[j]= getf(j - 1);
			}
		}
	}
	for(int i= 1; i <= n; i++) cout << c[i] << endl;
	return 0;
}