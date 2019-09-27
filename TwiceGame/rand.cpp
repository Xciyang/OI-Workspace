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
inline int putK(int l, int r) {
	int _i= rand() % (r - l + 1) + l;
	cout << _i << ' ';
	return _i;
}
int h[5005];
int main() {
	int n= putR(4000, 4000);
	for(int i= 1; i <= n; i++) {
		if(rand() % 2 && h[i - 1] == 0)
			putK(0, min(n - i + 1, 5));
		else
			putK(0, max(h[i - 1] - 1, 0));
	}
	return 0;
}
/*
50
0 0 4 1 6 6 0 4 0 0 9 0 7 1 0 5 0 0 0 4 5 0 0 1 5 5 1 0 1 6 1 0 0 3 2 0 0 5 0 9 0 0 5 5 10 10 0 0 1 6
*/