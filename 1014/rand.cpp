#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;
int n, a[1000000];
long long randd() {
	return (long long)rand() * rand() % INT_MAX * (rand() * rand() % INT_MAX);
}
int main() {
	srand(time(0));
	n= 10;
	cout << n << endl;
	for(int i= 1; i <= n; i++) a[i]= rand() % 5 * 2 + i % 2 + 1;
	random_shuffle(a + 1, a + n + 1);
	for(int i= 1; i <= n; i++) cout << a[i] << ' ';
	cout << endl;
	return 0;
}