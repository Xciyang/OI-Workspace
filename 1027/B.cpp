#include <iostream>
#include <stdio.h>
#include <map>
#include <algorithm>
using namespace std;
int n, a[300005];
double bestans;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1, greater< int >());
	long long sum= 0;
	for(int i= 1; i <= n; i++) sum+= a[i], bestans= max(bestans, (double)sum * sum / i);
	printf("%.9lf\n", bestans);
	return 0;
}