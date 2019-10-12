#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
using namespace std;
long long n, k, a[500005], sum[500005];
inline int judge(long long p) {
	long long cnt= 0, cnt2= 0, q= 0, i= 0, i2= 0, rang= sqrt(p) + 1;
	memset(sum, 0, sizeof(sum));
	for(int j= n; j; j--) {
		if(sum[j + 1]) {
			cnt+= sum[j + 1];
			i+= sum[j + 1] * (j + 1);
			i2+= sum[j + 1] * (j + 1) * (j + 1);
		}
		if(j + rang <= n && sum[j + rang]) {
			cnt-= sum[j + rang];
			i-= sum[j + rang] * (j + rang);
			i2-= sum[j + rang] * (j + rang) * (j + rang);
		}
		q= cnt * p - i2 + 2LL * i * j - 1LL * j * j * cnt;
		if(a[j] > q) {
			q= (a[j] - q) / p + ((a[j] - q) % p != 0);
			sum[j]= q, cnt2+= q;
			if(cnt2 > k) return 0;
		}
	}
	return 1;
}
int main() {
	cin >> n >> k;
	for(int i= 1; i <= n; i++) cin >> a[i], ++a[i];
	long long l= 1, r= 1e17, mid, ans= -1;
	while(l <= r) {
		mid= (l + r) >> 1;
		if(judge(mid))
			ans= mid, r= mid - 1;
		else
			l= mid + 1;
	}
	cout << ans << endl;
	return 0;
}