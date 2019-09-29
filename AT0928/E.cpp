#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int n, m, a[1005], b[1005], c[1005][12], f[1 << 12], maxx, w[1 << 12];
int getx(int x) {
	int res= 0;
	for(int i= 1; i <= b[x]; i++) res+= (1 << (c[x][i] - 1));
	return res;
}
int getg(int x) {
	int res= 0;
	while(x) ++res, x-= (x & -x);
	return res;
}
int main() {
	cin >> n >> m, maxx= (1 << n);
	for(int i= 0; i < maxx; i++) w[i]= getg(i);
	for(int i= 1; i <= m; i++) {
		cin >> a[i] >> b[i];
		for(int j= 1; j <= b[i]; j++) cin >> c[i][j];
	}
	memset(f, 0x3f, sizeof(f));
	for(int i= 1, j; i <= m; i++) {
		j= getx(i);
		for(int k= j; k; k= (k - 1) & j) f[k]= min(f[k], a[i]);
	}
	for(int i= 1; i <= n; i++) {
		for(int j= 0; j < maxx; j++) {
			if(w[j] != i) continue;
			for(int k= 0; k < maxx; k++) {
				if(j == k || w[k] >= i || (k & (~j))) continue;
				f[j]= min(f[j], f[k] + f[k ^ j]);
			}
		}
	}
	if(f[maxx - 1] == 0x3f3f3f3f) f[maxx - 1]= -1;
	cout << f[maxx - 1] << endl;
	return 0;
}