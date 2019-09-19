#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
using namespace std;
int setupRand() {
	srand(time(0));
	return 1;
}
int _b= setupRand();
unsigned long long Rand() {
	return (unsigned long long)rand() * rand() * rand() + rand() * rand() + rand();
}
#define rand() Rand()
inline int putR(int l, int r) {
	int _i= rand() % (r - l + 1) + l;
	cout << _i << endl;
	return _i;
}
int a[1005], to[100006], b[100006];
int main() {
	int n= putR(4000, 4000);
	for(int i= 2; i <= n; i++) {
		to[i]= rand() % (i - 1) + 1, b[i]= rand() % 100000;
		printf("%d %d %d\n", to[i], i, b[i]);
	}
	return 0;
}