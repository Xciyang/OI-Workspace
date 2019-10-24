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
	int n= putR(12, 13);
	putchar(' ');
	int m= putR(5, n - 1);
	putchar('\n');
	for(int i= 1; i <= n; i++) {
		if(rand() % 2) {
			a[i]= putR(1, m), putchar(' ');
		}
		else {
			int flag= 0;
			for(; i <= n; i++) {
				if(flag)
					a[i]= putR(1, max(a[i - 1] - 1, 1));
				else
					a[i]= putR(min(m, a[i - 1] + 1), m);
				flag^= 1, putchar(' ');
				if(rand() % 2) break;
			}
		}
	}
	putchar('\n');
	return 0;
}