#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;
int n, tmpx, t;
struct MAT {
	int a[100][100];
} base, ans;
int N;
MAT mul(const MAT &a, const MAT &b) {
	MAT res;
	memset(&res, 0, sizeof(res));
	for(int i= 1; i <= N; i++) {
		for(int j= 1; j <= N; j++) {
			for(int k= 1; k <= N; k++) {
				res.a[i][k]= (res.a[i][k] + a.a[i][j] * b.a[j][k]) % 2009;
			}
		}
	}
	return res;
}
void qpow() {
	ans= base, --t;
	while(t) {
		if(t & 1) ans= mul(ans, base);
		base= mul(base, base), t>>= 1;
	}
	return;
}
inline int query(int x, int k) {
	return x * 9 + k - 8;
}
int main() {
	scanf("%d%d", &n, &t);
	N= query(n, 9);
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= 8; j++) base.a[query(i, j)][query(i, j - 1)]= 1;
		for(int j= 1; j <= n; j++) {
			scanf("%01d", &tmpx);
			if(tmpx) base.a[query(i, 0)][query(j, tmpx - 1)]= 1;
		}
	}
	qpow();
	cout << ans.a[query(1, 0)][query(n, 0)] << endl;
	return 0;
}