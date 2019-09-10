#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
int n, m, k, b[100010], qlen, c[1200010];
long long ans[100010], nowans;
struct querys {
	int id, l, r, bl;
	bool operator<(const querys &q2) const {
		return bl == q2.bl ? r < q2.r : l < q2.l;
	}
} qs[100010];
inline void add(int x) {
	nowans+= (long long)c[x ^ k], ++c[x];
	return;
}
inline void del(int x) {
	--c[x], nowans-= (long long)c[x ^ k];
	return;
}
int main() {
	cin >> n >> m >> k, qlen= sqrt(n);
	for(int i= 1; i <= n; i++) cin >> b[i], b[i]^= b[i - 1];
	for(int i= 1; i <= m; i++) {
		cin >> qs[i].l >> qs[i].r, --qs[i].l;
		qs[i].id= i, qs[i].bl= (qs[i].l - 1) / qlen + 1;
	}
	sort(qs + 1, qs + m + 1);
	int l= 0, r= 0;
	c[0]= 1;
	for(int i= 1; i <= m; i++) {
		while(l < qs[i].l) del(b[l++]);
		while(l > qs[i].l) add(b[--l]);
		while(r < qs[i].r) add(b[++r]);
		while(r > qs[i].r) del(b[r--]);
		ans[qs[i].id]= nowans;
	}
	for(int i= 1; i <= m; i++) cout << ans[i] << endl;
	return 0;
}