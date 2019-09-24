#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, ans[100005], sum[100005], maxs[100005], d[100005];
struct FJ {
	int a, s;
	inline int operator<(const FJ &f2) const {
		return a > f2.a;
	}
} fjs[100005];
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> fjs[i].s;
	for(int i= 1; i <= n; i++) cin >> fjs[i].a;
	sort(fjs + 1, fjs + n + 1);
	for(int i= 1; i <= n; i++) sum[i]= sum[i - 1] + fjs[i].a, maxs[i]= max(maxs[i - 1], fjs[i].s);
	for(int i= n; i; i--) d[i]= max(d[i + 1], fjs[i].s * 2 + fjs[i].a);
	for(int i= 1; i <= n; i++) cout << max(sum[i] + maxs[i] * 2, sum[i - 1] + d[i]) << endl;
	return 0;
}