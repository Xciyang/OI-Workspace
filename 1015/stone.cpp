#include <iostream>
#include <stdio.h>
using namespace std;
int n, a[100005], wp[100005];
double ans;
void dfs(double p, int times, long long nowt) {
	for(int i= 2; i <= n; i++) {
		if(wp[i]) continue;
		wp[i]= 1;
		dfs(p * a[i] / nowt, times + 1, nowt - a[i]);
		wp[i]= 0;
	}
	ans+= (double)a[1] * times * p / nowt;
	return;
}
long long tot;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i], tot+= a[i];
	// if(tot < 10000007) {
	// 	f[0]= 1;
	// 	for(int i= 2; i <= n; i++)
	// 		for(int j= tot; j >= a[i]; j--) f[j]+= f[j - a[i]];
	// 	for(int i= 0; i <= tot; i++) tot2+= f[i];
	// 	for(int i= 0; i <= tot; i++) ans+= ((double)i + a[1]) * f[i] / tot2;
	// 	cout << ans << endl;
	// }
	dfs(1, 1, tot);
	printf("%.6lf\n", ans);
	return 0;
}