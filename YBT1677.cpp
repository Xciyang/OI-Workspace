#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m, d1[101], d2[101], min1= 0x3f3f3f3f, min2= 0x3f3f3f3f;
int f[200];
int judge(int x) {
	memset(f, ~0x7f, sizeof(f)), f[0]= 0;
	for(int i= 1; i <= n; i++) {
		for(int j= m; j >= 0; j--)
			for(int k= x / d1[i]; k >= 0; k--) f[j + k]= max(f[j + k], f[j] + (x - k * d1[i]) / d2[i]);
	}
	return f[m] >= m;
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) cin >> d1[i] >> d2[i], min1= min(min1, d1[i] * m), min2= min(min2, d2[i] * m);
	int l= 0, r= min1 + min2, mid, ans= -1;
	while(l <= r) {
		mid= (l + r) >> 1;
		if(judge(mid))
			r= mid - 1, ans= mid;
		else
			l= mid + 1;
	}
	cout << ans << endl;
	return 0;
}