#include <iostream>
#include <stdio.h>
using namespace std;
const int p= 1e9 + 7;
int n, m, a[105];
template < typename T >
void read(T &e) {
	int f= 1;
	e= 0;
	char ch= getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') e= ((long long)e * 10 + ch - '0') % p, ch= getchar();
	e*= f;
	return;
}
int judge(int x) {
	int sum= 0;
	for(int i= n; i; i--) sum= ((long long)sum + a[i]) * x % p;
	return !((sum + a[0]) % p);
}
int ans[1000006], aptr;
int put(int x) {
	if(x > 9) put(x / 10);
	return putchar('0' + x % 10);
}
int main() {
	read(n), read(m);
	for(int i= 0; i <= n; i++) read(a[i]);
	for(int i= 1; i <= m; i++)
		if(judge(i)) ans[++aptr]= i;
	put(aptr), putchar('\n');
	for(int i= 1; i <= aptr; i++) put(ans[i]), putchar('\n');
	return 0;
}