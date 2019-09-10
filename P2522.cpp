#include <iostream>
#include <stdio.h>
#define MAXA 50001
using namespace std;
int miu[50005], notzs[50005], zs[50005], sum[50005];
void shai() {
	notzs[1]= 1, miu[1]= 1;
	for(int i= 2; i <= MAXA; i++) {
		if(!notzs[i]) miu[i]= -1, zs[++zs[0]]= i;
		for(int j= 1; j <= zs[0] && i * zs[j] <= MAXA; j++) {
			notzs[i * zs[j]]= 1;
			if(i % zs[j] == 0) {
				miu[i * zs[j]]= 0;
				break;
			}
			miu[i * zs[j]]= -miu[i];
		}
	}
	for(int i= 1; i <= MAXA; i++) sum[i]= sum[i - 1] + miu[i];
	return;
}
int query(int n, int m, int k) {
	int res= 0;
	n/= k, m/= k;
	if(n > m) swap(n, m);
	for(int i= 1, j; i <= n; i= j + 1) {
		j= min(n / (n / i), m / (m / i));
		res+= (sum[j] - sum[i - 1]) * (n / i) * (m / i);
	}
	return res;
}
#define query(x, y) query(x, y, k)
int t;
int main() {
	shai();
	cin >> t;
	int a, b, c, d, k;
	while(t--) {
		cin >> a >> b >> c >> d >> k;
		cout << query(b, d) - query(b, c - 1) - query(a - 1, d) + query(a - 1, c - 1) << endl;
	}
	return 0;
}