#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m;
struct MAT {
	int r, c, a[105][105];
	inline MAT operator*(const MAT &m2) const {
		MAT res;
		memset(&res, 0, sizeof(res));
		res.r= r, res.c= m2.c;
		for(int i= 1; i <= r; i++) {
			for(int j= 1; j <= c; j++) {
				for(int k= 1; k <= m2.c; k++) {
					res.a[i][k]= (res.a[i][k] + a[i][j] * m2.a[j][k]) % 30011;
				}
			}
		}
		return res;
	}
} basem, ans;
inline MAT qpow(MAT a, int b) {
	MAT res= a;
    --b;
	while(b) {
		if(b & 1) res= res * a;
		a= a * a, b>>= 1;
	}
	return res;
}
inline int query(int x, int y) {
	return (x - 1) * 2 + y;
}
int main() {
	cin >> n >> m;
	basem.r= n * 2, basem.c= n * 2;
	for(int i= 1; i <= n; i++) {
		++basem.a[query(i, 1)][query(i, 1)];
		++basem.a[query(i, 2)][query(i, 2)];
		for(int j= i - 1; j <= i + 1; j++) {
			if(j < 1 || j > n) continue;
			++basem.a[query(i, 1)][query(j, 2)];
			++basem.a[query(i, 2)][query(j, 1)];
			for(int k= j - 1; k <= j + 1; k++) {
				if(k < 1 || k > n) continue;
				++basem.a[query(i, 2)][query(k, 2)];
			}
		}
	}
	ans.r= n * 2, ans.c= 1;
	ans.a[query(1, 1)][1]= ans.a[query(1, 2)][1]= ans.a[query(2, 2)][1]= 1;
	cout << ((qpow(basem, (m + 1) / 2 - 1) * ans).a[query(n, ((m + 1) % 2) + 1)][1] - (qpow(basem, (m - 1) / 2 - 1) * ans).a[query(n, ((m + 1) % 2) + 1)][1] + 30011) % 30011 << endl;
	return 0;
}
