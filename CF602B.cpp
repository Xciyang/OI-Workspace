#include <iostream>
#include <stdio.h>
using namespace std;
int n, a[100005], f[100005], nowk, maxx, minx, ans= 1, nowans;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i];
	for(int i= 1; i <= n - ans; i++) {
		minx= maxx= a[i], nowans= 1;
		for(int j= i + 1; j <= n; j++, nowans++) {
			minx= min(minx, a[j]), maxx= max(maxx, a[j]);
			if(maxx - minx > 1) break;
		}
		ans= max(ans, nowans);
	}
	cout << ans << endl;
	return 0;
}