#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
int q, k;
int main() {
	cin >> q;
	while(q--) {
		cin >> k;
		long long l= 0, r= 50000, mid, ans= 0;
		while(l <= r) {
			mid= (l + r) >> 1;
			if(mid * (mid + 1) / 2 > k)
				r= mid - 1;
			else
				l= mid + 1, ans= mid;
		}
		cout << k - ans * (ans + 1) / 2 << endl;
	}
	return 0;
}