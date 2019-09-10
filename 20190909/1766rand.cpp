#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
using namespace std;
int n, A, B, tmpx;
long long randd() {
	return (long long)rand() * rand() % INT_MAX * (rand() * rand() % INT_MAX);
}
int main() {
	srand(time(0));
	n= 10;
	cout << n << endl;
	A= randd() % 100 + 1, B= randd() % 10 + 1;
	cout << A << ' ' << B << endl;
	for(int i= 1; i <= n; i++) {
		cout << randd() % 10 + 1 << ' ';
	}
	cout << endl;
	return 0;
}