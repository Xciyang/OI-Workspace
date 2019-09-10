#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
int isZS(int x) {
	for(int i= 2; i <= sqrt(x); i++)
		if(x % i == 0) return false;
	return true;
}
int n;
int main() {
	while(true) {
		cin >> n;
		if(!n) break;
		for(int i= 1; i <= n; i++) {
			if(n % i == 0 && isZS(n / i)) {
				cout << n / i << endl;
				break;
			}
		}
	}
	return 0;
}