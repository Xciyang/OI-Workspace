#include <iostream>
#include <stdio.h>
using namespace std;
int a1, a2, k1, k2, n, ans1, ans2;
int main() {
	cin >> a1 >> a2 >> k1 >> k2 >> n;
	if(k1 > k2) swap(a1, a2), swap(k1, k2);
	if(n > a1 * k1) {
		ans1= min(a1 + (n - a1 * k1) / k2, a1 + a2);
	}
	else {
		ans1= n / k1;
	}
	n-= (k1 - 1) * a1 + (k2 - 1) * a2;
	if(n > 0) ans2= min(a1 + a2, n);
	cout << ans2 << ' ' << ans1 << endl;
	return 0;
}