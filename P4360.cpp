#include <iostream>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#define int long long
using namespace std;
int n, w[20010], d[20010], jm[2], ans, nowans, cha, wd;
int clacm() {
	int x= min(jm[0], jm[1]), y= max(jm[0], jm[1]);
	return d[x] * w[x] + d[y] * (w[y] - w[x]) + d[n + 1] * (w[n] - w[y]) - wd;
}
const long double BeginT= 40000, EndT= 1e-1, changeT= 0.99;
void SA() {
	for(register long double T= BeginT; T > EndT; T*= changeT) {
		int x= rand() % n + 1, y= rand() % 2;
		while(jm[0] == x || jm[1] == x) x= rand() % n + 1;
		swap(x, jm[y]), nowans= clacm(), cha= ans - nowans;
		if(nowans <= ans)
			ans= nowans;
		else if(exp(cha / T) < (double)rand() / RAND_MAX)
			swap(x, jm[y]);
	}
	return;
}
signed main() {
	srand(time(0)), scanf("%lld", &n), ans= LONG_LONG_MAX;
	for(int i= 1; i <= n; i++) scanf("%lld%lld", w + i, d + i + 1), wd+= w[i] * d[i], w[i]+= w[i - 1], d[i + 1]+= d[i];
	if(n == 2) {
		jm[0]= 1, jm[1]= 2, ans= clacm();
		printf("%lld\n", ans);
		return 0;
	}
	

	jm[0]= rand() % n + 1, jm[1]= rand() % n + 1;
	while((double)clock() / CLOCKS_PER_SEC < 0.9) SA();
	printf("%lld\n", ans);
	return 0;
}