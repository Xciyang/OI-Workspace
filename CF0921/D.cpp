#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
int n, a[200005], maxx, tmpx;
long long ans;
inline int gcd(int x, int y) {
	return y ? gcd(y, x % y) : x;
}
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i], maxx= max(maxx, a[i]);
	tmpx= maxx - a[1];
	for(int i= 2; i <= n; i++) tmpx= gcd(tmpx, maxx - a[i]);
	for(int i= 1; i <= n; i++) ans+= (maxx - a[i]) / tmpx;
	cout << ans << ' ' << tmpx << endl;
	return 0;
}