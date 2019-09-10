#include <iostream>
#include <stdio.h>
using namespace std;
int n, a[1000006];
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i], a[i]^= a[i - 1];
	cout << a[n] << endl;
	return 0;
}