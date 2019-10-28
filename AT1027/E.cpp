#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <queue>
#include <math.h>
using namespace std;
long long n, k, ans;
int a[1000005], b[1000005];
inline int check(long long x) {
	long long res= 0, y;
	for(int i= 1; i <= n; i++) {
		y= x / b[n - i + 1];
		if(a[i] > y) res+= a[i] - y;
	}
	return res <= k;
}
int main() {
	cin >> n >> k;
	for(int i= 1; i <= n; i++) cin >> a[i];
	for(int i= 1; i <= n; i++) cin >> b[i];
	sort(a + 1, a + n + 1), sort(b + 1, b + n + 1);
	long long l= 0, r= 1e15, mid;
	while(l <= r) {
		mid= (l + r) >> 1;
		if(check(mid))
			r= mid - 1, ans= mid;
		else
			l= mid + 1;
	}
	cout << ans << endl;
	return 0;
}
