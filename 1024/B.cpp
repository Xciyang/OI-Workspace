#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
// namespace BL {
// int n, b[100], ans;
// inline int count(int x) {
// 	int res= 0;
// 	while(x) x-= (x & -x), ++res;
// 	return res;
// }
// void dfs(int tot, int last) {
// 	for(int i= last; i <= n - tot; i++) {
// 		++b[i];
// 		dfs(tot + i, i);
// 		--b[i];
// 	}
// 	int nowans= 0;
// 	for(int i= 1; i <= last; i++) nowans+= count(b[i]);
// 	ans= max(ans, nowans);
// 	return;
// }
// void work(int t) {
// 	for(int i= 1; i <= t; i++) {
// 		n= i, ans= 0, memset(b, 0, sizeof(b));
// 		dfs(0, 1);
// 		cout << i << ':' << ans << endl;
// 	}
// 	return;
// }
// }  // namespace BL

#define MAXN 20000000
int t;
long long n, a[MAXN + 7], sum[MAXN + 7];
void init() {
	a[1]= 1, a[2]= 1, sum[2]= 1;
	for(int i= 3; i <= MAXN; i++) {
		a[i]= a[i - a[i - 1]] + a[i - 1 - a[i - 2]];
		sum[i]= sum[i - 1] + a[i];
	}
	return;
}
int main() {
	init(), scanf("%d", &t);
	// BL::work(t);
	while(t--) {
		scanf("%lld", &n);
		int l= 2, r= MAXN, mid, ans= 2;
		while(l <= r) {
			mid= (l + r) >> 1;
			if(n == sum[mid]) {
				ans= mid;
				break;
			}
			if(n > sum[mid])
				l= mid + 1, ans= mid;
			else
				r= mid - 1;
		}
		cout << ans - 1 << endl;
	}

	// while(t--) {
	// 	cin >> n;
	// 	ans= 0, memset(b, 0, sizeof(b));
	// 	dfs(0, 1);
	// 	cout << ans << endl;
	// }
	return 0;
}
/*
1, 1, 2, 2, 3, 4, 4, 4, 5, 6, 6, 7, 8, 8, 8, 8, 9, 10, 10, 11, 12, 12, 12, 13, 14, 14, 15, 16, 16, 16, 16, 16, 17, 18, 18, 19, 20, 20, 20, 21, 22, 22, 23, 24, 24, 24, 24, 25, 26, 26, 27, 28, 28, 28, 29, 30, 30, 31, 32, 32, 32, 32, 32, 32, 33, 34, 34,
35, 36, 36, 36, 37

1, 1, 2, 2, 3, 4, 4, 4, 5, 6, 7, 7, 8, 8, 8, 8, 9, 10, 11, 12, 12, 13, 14, 14, 15, 15, 15, 16, 16, 16, 16, 16, 17, 18, 19, 20, 21, 21, 22, 23, 24, 24, 25, 26, 26, 27, 27, 27, 28, 29, 29, 30, 30, 30, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 33, 34, 35,
36, 37, 38, 38, 39, 40, 41, 42

(1 1) 2 2 3 4  4  4  5  6  6  7  8 8  8  8  9  10 10/11?

	  1 3 5 8 12 16 20 25 31 37 44 52 60 68 76 85 95

a(1) = a(2) = 1, a(n) = a(n - a(n - 1)) + a(n - 1 - a(n - 2))

*/