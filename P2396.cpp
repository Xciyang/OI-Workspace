#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, dis[1 << 24], ey[2], j, f[1 << 24];
// 卡常题
int main() {
	cin >> n;
	for(int i= 0; i < n; i++) cin >> dis[1 << i];
	cin >> m;
	for(int i= 0; i < m; i++) cin >> ey[i];
	f[0]= 1;
	for(int i= 1; i < (1 << n); i++) {
		j= i & -i, dis[i]= dis[i ^ j] + dis[j];
		if(dis[i] == ey[0] || dis[i] == ey[1]) continue;
		for(int k= i; k; k^= j) {
			j= k & -k;
			f[i]+= f[i ^ j];
			if(f[i] >= 1000000007) f[i]-= 1000000007;
		}
	}
	cout << f[(1 << n) - 1] << endl;
	return 0;
}