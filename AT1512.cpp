#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, a, tmpx, cnt[100005];
int main() {
	scanf("%d%d", &n, &m), a= n;
	while(a--)
		if(++cnt[scanf("%d", &tmpx), tmpx] > n / 2) return printf("%d\n", tmpx), 0;
	return printf("?\n"), 0;
}