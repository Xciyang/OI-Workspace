#include <iostream>
#include <stdio.h>
using namespace std;
int n, k, q, a[2000006], ta[2000006], flag, tmpx, tmpy;
long long v[2000006];
inline int lowb(int x) {
	return x & -x;
}
inline void change(int x, long long c) {
	for(; x <= n; x+= lowb(x)) v[x]+= c;
	return;
}
inline long long query(int x) {
	long long res= 0;
	for(; x; x-= lowb(x)) res+= v[x];
	return res;
}
void print(int x) {
	if(x) {
		printf("No\n");
	}
	else {
		printf("Yes\n");
	}
	return;
}
int main() {
	freopen("august.in", "r", stdin);
	freopen("august.out", "w", stdout);
	scanf("%d%d%d", &n, &k, &q);
	for(int i= 1; i <= n; i++) scanf("%d", a + i);
	for(int i= 1; i <= n; i++) v[i]= 0;
	flag= 0;
	for(int i= 1; i <= n; i++) {
		int realv= a[i] + query(i);
		if(!realv) continue;
		if(i + k - 1 > n) {
			flag= 1;
			break;
		}
		change(i, -realv);
		change(i + k, realv);
	}
	print(flag);
	for(int i= 1; i <= q; i++) {
		scanf("%d%d", &tmpx, &tmpy);
		a[tmpx]+= tmpy;
		for(int j= 1; j <= n; j++) v[j]= 0;
		flag= 0;
		for(int j= 1; j <= n; j++) {
			int realv= a[j] + query(j);
			if(!realv) continue;
			if(j + k - 1 > n) {
				flag= 1;
				break;
			}
			change(j, -realv);
			change(j + k, realv);
		}
		print(flag);
	}
	return 0;
}
/*
5 2 5
1 1 1 2 1
3 -1
1 -1
3 1
3 1
1 -1

*/