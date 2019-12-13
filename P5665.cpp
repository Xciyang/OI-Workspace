#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
inline int read() {
	int e = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		e = e * 10 + ch - '0';
		ch = getchar();
	}
	return e * f;
}
int n, m;
long long a[500005], sum[500005], f[500005], maxf[500005], ans, tmpx;
template < typename T >
inline T maxl(T a, T b) {
	return a > b ? a : b;
}
template < typename T >
inline T minl(T a, T b) {
	return a < b ? a : b;
}
deque< int > qu;
int main() {
	n = read(), m = read();
	if(m == 0) {
		for(int i = 1; i <= n; i++) a[i] = read(), sum[i] = sum[i - 1] + a[i];
		qu.push_back(0);
		for(int i = 1; i <= n; i++) {
			int l = 0, r = qu.size() - 1, mid, ans = r;
			while(l <= r) {
				mid = (l + r) >> 1;
				if(sum[i] < maxf[qu[mid]] + sum[qu[mid]])
					r = mid - 1;
				else
					l = mid + 1, ans = mid;
			}
			maxf[i] = sum[i] - sum[qu[ans]];
			while(!qu.empty() && sum[i] + maxf[i] <= maxf[qu.back()] + sum[qu.back()]) qu.pop_back();
			qu.push_back(i);
		}
		for(int i = n; i; i--) {
			tmpx += a[i];
			if(tmpx >= maxf[i - 1]) {
				ans += tmpx * tmpx;
				tmpx = 0;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
