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
int a[400005];
int main() {
	int n= putR(400000, 400000);
	for(int i= 1; i <= n; i++) a[i]= i + 1;
	a[n]= 1;
	int x= rand() % n + 1, y= rand() % n + 1;
	while(x == y) y= rand() % n + 1;
	a[x]= y;
	for(int i= 1; i <= n; i++) cout << a[i] << ' ';
	cout << endl;
	int m= putR(300000, 300000);
	for(int i= 1; i <= m; i++) printf("%d %d %d\n", rand() % n + 1, rand() % (int)1e9 + 1, rand() % (int)1e9+ 1);
	return 0;
}