#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
int n, m, r[16], h[16];
int ans= 0x3f3f3f3f;
void dfs(int nowc, int total, int lastq) {
	int lastc= m - nowc + 1;
	if(total + r[1] * r[1] + lastc >= ans) return;
	if(nowc > m) {
		if(lastq == 0) ans= total + r[1] * r[1];
		return;
	}
	if(lastq > r[nowc - 1] * r[nowc - 1] * h[nowc - 1] * lastc) return;
	for(int i= r[nowc - 1] - 1; i >= lastc; i--) {
		for(int j= h[nowc - 1] - 1; j >= lastc; j--) {
			if(i * i * j > lastq) continue;
			r[nowc]= i, h[nowc]= j;
			dfs(nowc + 1, total + 2 * i * j, lastq - i * i * j);
		}
	}
	return;
}
int main() {
	cin >> n >> m;
	r[0]= h[0]= sqrt(n) + 1;
	dfs(1, 0, n);
	if(ans == 0x3f3f3f3f) ans= 0;
	cout << ans << endl;
	return 0;
}