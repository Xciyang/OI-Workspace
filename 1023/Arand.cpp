#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <process.h>
using namespace std;
int setupRand() {
	srand(time(0) + getpid());
	return 1;
}
int _b= setupRand();
unsigned long long Rand() {
	return (unsigned long long)rand() * rand() * rand() + rand() * rand() + rand();
}
#define rand() Rand()
inline int putR(int l, int r) {
	int _i= (rand() % (r - l + 1)) + l;
	cout << _i;
	return _i;
}
int a[400005];
int main() {
	int n= putR(5, 5);
	putchar('\n');
	for(int i= 1; i <= n; i++) putR(1, 5), putchar(' ');
	putchar('\n');
	putR(1, 2);
	putchar('\n');
	return 0;
}