#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, q, tmpx, tmpy, tmpz, tmpk, tmpp;
int a[100005], b[100005];

int main() {
	cin >> n >> m >> q;
	while(q--) {
		cin >> tmpx;
		if(tmpx == 1) {
			cin >> tmpx >> tmpy;
		}
		else {
			cin >> tmpx >> tmpy >> tmpz >> tmpk;
		}
	}
	return 0;
}