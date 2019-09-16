#include <iostream>
#include <stdio.h>
using namespace std;
int n, k, q, a[100005], tmpx;
int main() {
	cin >> n >> k >> q;
	for(int i= 1; i <= q; i++) cin >> tmpx, ++a[tmpx];
	for(int i= 1; i <= n; i++) {
		if(k - q + a[i] > 0) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
	}
	return 0;
}