#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, a[200005], sum[200005];
double bestans;
void tf(int x) {
	int l= 1, r= min(x - 1, n - x), mid;
	double res= a[x], tmpx;
	while(l <= r) {
		mid= (l + r) >> 1, tmpx= ((double)sum[x] - sum[x - mid - 1] + sum[n] - sum[n - mid]) / (mid * 2 + 1);
		if(tmpx >= ((double)sum[x] - sum[x - mid] + sum[n] - sum[n - mid + 1]) / (mid * 2 - 1))
			l= mid + 1, res= tmpx;
		else
			r= mid - 1;
	}
	bestans= max(bestans, res - a[x]);
	return;
}
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	for(int i= 1; i <= n; i++) sum[i]= sum[i - 1] + a[i];
	for(int i= 2; i < n; i++) tf(i);
	printf("%.5lf\n", bestans);
	return 0;
}