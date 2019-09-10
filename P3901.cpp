#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int n, q, a[1000005], last[1000005], maxl[1000005], tmpx, tmpy;
int main() {
	cin >> n >> q;
	for(int i= 1; i <= n; i++) cin >> a[i];
	for(int i= 1; i <= n; i++) {
		maxl[i]= max(maxl[i - 1], last[a[i]]);
		last[a[i]]= i;
	}
	while(q--) {
		cin >> tmpx >> tmpy;
		cout << (maxl[tmpy] >= tmpx ? "No" : "Yes") << endl;
	}
	return 0;
}