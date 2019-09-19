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
	int n= putR(100, 100), m= putR(100, 100);
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) printf("%d ", i * 4 - j * 9);
		printf("\n");
	}
	return 0;
}