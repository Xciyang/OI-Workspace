#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
using namespace std;
#define int long long
int T, n;
long long v[40], ans;
const long double beginT= 10000, EndT= 1e-12, ChangeT= 0.998;
inline long long absl(long long a) {
	return a > 0 ? a : -a;
}
void SA() {
	long long lsum= 0, rsum= 0;
	for(int i= 1; i <= (n >> 1); i++) lsum+= v[i];
	for(int i= (n >> 1) + 1; i <= n; i++) rsum+= v[i];
	for(long double t= beginT; t > EndT; t*= ChangeT) {
		int x= rand() % (n >> 1) + 1, y= rand() % (n - (n >> 1)) + 1;
		lsum= lsum - v[x] + v[(n >> 1) + y], rsum= rsum + v[x] - v[(n >> 1) + y], swap(v[x], v[(n >> 1) + y]);
		long long nowans= absl(lsum - rsum), cha= ans - nowans;
		if(cha >= 0)
			ans= nowans;
		else if(exp(cha / t) < (double)rand() / RAND_MAX)
			lsum= lsum - v[x] + v[(n >> 1) + y], rsum= rsum + v[x] - v[(n >> 1) + y], swap(v[x], v[(n >> 1) + y]);
	}
	return;
}
signed main() {
	srand(time(0));
	scanf("%lld", &T);
	while(T--) {
		scanf("%lld", &n), ans= LONG_LONG_MAX;
		for(int i= 1; i <= n; i++) scanf("%lld", v + i);
		if(n == 1) {
			printf("%lld\n", v[1]);
			continue;
		}
		for(int i= 0; i < 6; i++) SA();
		printf("%lld\n", ans);
	}
	return 0;
}