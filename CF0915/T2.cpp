#include <iostream>
#include <stdio.h>
using namespace std;
int n, a[200005];
long long ans[2], base[2], tmp;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i], a[i]= a[i] < 0 ? 0 : 1;
	for(int i= 1; i <= n; i++) {
		if(a[i]) {
			ans[1]+= base[1] + 1, ans[0]+= base[0];
			base[1]= base[1] + 1;
		}
		else {
			ans[1]+= base[0], ans[0]+= base[1] + 1;
			tmp= base[0], base[0]= base[1] + 1, base[1]= tmp;
		}
	}
	cout << ans[0] << ' ' << ans[1] << endl;
	return 0;
}