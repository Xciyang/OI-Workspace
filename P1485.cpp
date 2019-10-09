#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
long long n, k, a[500005], v[500005];
inline int judge(long long p) {
	for(int i= 1; i <= n; i++) v[i]= a[i] + 1;
	long long cnt= 0, q;
	for(int i= n; i; i--) {
		if(v[i] <= 0) continue;
		q= v[i] / p + (v[i] % p != 0), cnt+= q;
		q= p * q;
		if(cnt > k) return 0;
		for(int j= i; j && q - (i - j) * (i - j) > 0; j--) v[j]-= q - (i - j) * (i - j);
	}
	return 1;
}
int main() {
	cin >> n >> k;
	for(int i= 1; i <= n; i++) cin >> a[i];
	long long l= 1, r= 1e15, mid, ans= -1;
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