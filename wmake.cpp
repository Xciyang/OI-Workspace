#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <set>
using namespace std;
template < class T >
inline void write(T x) {
	if(x == 0) return (void)putchar('0');
	if(x < 0) putchar('-'), x= -x;
	static char buf[30];
	char *p= buf;
	while(x) {
		*(p++)= x % 10 + '0';
		x/= 10;
	}
	while(p > buf) putchar(*(--p));
}
int n, m;
char JSB[4]= "JSB";
int surand(){
	return (unsigned long long)rand() * rand() % 2147483647;
}
inline int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
int main() {
	srand(time(0));
	n= 2000000 + surand() % 1000000, m= 2000000 + surand() % 1000000;
	while(gcd(n, m) < 10000 || n == m || n * m / gcd(n, m) < 100000){
		n= 2000000 + surand() % 1000000, m= 2000000 + surand() % 1000000;
	}
	cout << n << endl;
	for(int i= 1; i <= n; i++) putchar(JSB[rand() % 3]);
	cout << endl << m << endl;
	return 0;
}