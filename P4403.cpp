#include <iostream>
#include <stdio.h>
#include <bitset>
using namespace std;
int t, n;
long long s[200005], e[200005], d[200005], l, r;
int judge(long long k) {
	int res= 0;
	for(int i= 1; i <= n; i++) {
		if(k < s[i]) continue;
		res+= (min(k, e[i]) - s[i]) / d[i] + 1;
	}
	return res % 2;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		l= 0, r= 0;
		for(int i= 1; i <= n; i++) scanf("%lld%lld%lld", s + i, e + i, d + i), r= max(r, s[i] + (e[i] - s[i]) / d[i] * d[i]);
		if(!judge(r))
			printf("Poor QIN Teng:(\n");
		else {
			long long mid, ans= 0;
			while(l <= r) {
				mid= (l + r) >> 1;
				if(judge(mid))
					r= mid - 1;
				else
					l= mid + 1;
			}
			for(int i= 1; i <= n; i++) {
				if(l < s[i] || l > e[i]) continue;
				ans+= ((l - s[i]) % d[i] == 0);
			}
            printf("%lld %lld\n", l, ans);
		}
	}
	return 0;
}
