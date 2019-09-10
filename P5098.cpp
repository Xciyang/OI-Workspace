#include <iostream>
#include <stdio.h>
using namespace std;
int n, tmpx, tmpy, a= 0x7f7f7f7f, b= -0x7f7f7f7f, c= 0x7f7f7f7f, d= -0x7f7f7f7f;
int main() {
	cin >> n;
	while(n--) {
		cin >> tmpx >> tmpy;
		a= min(a, tmpx + tmpy);
		b= max(b, tmpx + tmpy);
		c= min(c, tmpx - tmpy);
		d= max(d, tmpx - tmpy);
	}
	cout << max(b - a, d - c) << endl;
 	return 0;
}