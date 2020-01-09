#include <iostream>
#include <stdio.h>
using namespace std;
#define int long long
const int MAXN = 50000;
int miu[MAXN + 5], notzs[MAXN + 5], zs[MAXN + 5], sum[MAXN + 5], f[MAXN + 5];
void shai() {
	notzs[1] = 1, miu[1] = 1;
	for(int i = 2; i <= MAXN; i++) {
		if(!notzs[i]) miu[i] = -1, zs[++zs[0]] = i;
		for(int j = 1; j <= zs[0] && i * zs[j] <= MAXN; j++) {
			notzs[i * zs[j]] = 1;
			if(i % zs[j] == 0) {
				miu[i * zs[j]] = 0;
				break;
			}
			miu[i * zs[j]] = -miu[i];
		}
	}
	for(int i = 1; i <= MAXN; i++) {
		for(int l = 1, r; l <= i; l = r + 1) {
			r = i / (i / l);
			f[i] += (r - l + 1) * (i / l);
		}
		sum[i] = sum[i - 1] + miu[i];
	}
	return;
}
int query(int n, int m) {
	int res = 0;
	if(n > m) swap(n, m);
	for(int i = 1, j; i <= n; i = j + 1) {
		j = min(n / (n / i), m / (m / i));
		res += (sum[j] - sum[i - 1]) * f[n / i] * f[m / i];
	}
	return res;
}
int T, N, M;
signed main() {
    shai();
	cin >> T;
	while(T--) {
		cin >> N >> M;
		cout << query(N, M) << endl;
	}
	return 0;
}