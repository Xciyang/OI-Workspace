#include <iostream>
#include <stdio.h>
using namespace std;
int n, a[105], m, tmpx, tmpy;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i];
	cin >> m;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy;
		a[tmpx - 1]+= tmpy - 1;
		a[tmpx + 1]+= a[tmpx] - tmpy;
		a[tmpx]= 0;
	}
	for(int i= 1; i <= n; i++) cout << a[i] << endl;
	return 0;
}