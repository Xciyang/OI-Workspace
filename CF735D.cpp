#include <iostream>
#include <stdio.h>
using namespace std;
int n;
bool iszs(int x) {
	for(int i= 2; i * i <= x; i++)
		if(x % i == 0) return 0;
	return 1;
}
int main() {
	cin >> n;
	cout << (iszs(n) ? 1 : (n % 2 == 0 || iszs(n - 2) ? 2 : 3)) << endl;
	return 0;
}