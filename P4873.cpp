#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, t, tmpx, tmpy, cnt;
long long f[100005];
int main() {
	cin >> n >> t;
	for(int i= 1; i <= n; i++) {
		cin >> tmpx >> tmpy;
		long long y= -(1LL * tmpy * t + tmpx);
		if(i == 1)
			f[++cnt]= y;
		else {
			if(y >= f[cnt])
				f[++cnt]= y;
			else {
				int x= upper_bound(f + 1, f + cnt + 1, y) - f;
				f[x]= y;
			}
		}
	}
	cout << cnt << endl;
	return 0;
}