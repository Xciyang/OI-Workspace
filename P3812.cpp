#include <iostream>
#include <stdio.h>
using namespace std;
long long n, base[51], tmpx, ans;
int main() {
	cin >> n;
	for(int i= 0; i < n; i++) {
		cin >> tmpx;
		for(int j= 50; j > -1; j--) {
			if((1ll << j) & tmpx) {
				if(!base[j]) base[j]= tmpx;
				tmpx^= base[j];
			}
		}
	}
	for(int i= 50; i > -1; i--)
		if((ans ^ base[i]) > ans) ans^= base[i];
	cout << ans << endl;
	return 0;
}