#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;
inline int read() {
	int re= 0;
	char c= getchar();
	while(c > '9' || c < '0') c= getchar();
	while(c >= '0' && c <= '9') re= re * 10 + c - '0', c= getchar();
	return re;
}
template < class T >
inline void write(T x) {
	if(x > 9) write(x / 10);
	putchar('0' + x % 10);
	return;
}
int tmpx, n, k, a[5000001];
int main() {
	n= read(), k= read();
	for(int i= 1; i <= n; i++) a[i]= read();
	for(int i= 1; i <= k; i++) write(a[i]), putchar(' ');
	putchar('\n');
	return 0;
}