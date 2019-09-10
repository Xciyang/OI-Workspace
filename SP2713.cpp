#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
using namespace std;
inline int read() {
	register int x= 0, f= 1;
	register char ch= getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') x= (x << 3) + (x << 1) + ch - '0', ch= getchar();
	return x * f;
}
int cases, n, m, tmpx, tmpy, tmpz;
long long a[500001], sum[500001], maxa[500001];
void pushu(int nown) {
	maxa[nown]= max(maxa[nown << 1], maxa[nown << 1 | 1]);
	sum[nown]= sum[nown << 1] + sum[nown << 1 | 1];
	return;
}
void build(int nown, int l, int r) {
	if(l == r) {
		maxa[nown]= sum[nown]= a[l];
		return;
	}
	int mid= (l + r) >> 1;
	build(nown << 1, l, mid), build(nown << 1 | 1, mid + 1, r);
	pushu(nown);
	return;
}
void update(int nown, int l, int r, int ml, int mr) {
	if(l == r) {
		sum[nown]= maxa[nown]= sqrt(sum[nown]);
		return;
	}
	int mid= (l + r) >> 1;
	if(mid >= ml && maxa[nown << 1] > 1) update(nown << 1, l, mid, ml, mr);
	if(mid < mr && maxa[nown << 1 | 1] > 1) update(nown << 1 | 1, mid + 1, r, ml, mr);
	pushu(nown);
	return;
}
long long query(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) return sum[nown];
	int mid= (l + r) >> 1;
	long long ans= 0;
	if(mid >= ml) ans+= query(nown << 1, l, mid, ml, mr);
	if(mid < mr) ans+= query(nown << 1 | 1, mid + 1, r, ml, mr);
	return ans;
}
signed main() {
	scanf("%d", &n);
	memset(sum, 0, sizeof(sum));
	memset(maxa, 0, sizeof(maxa));
	for(int i= 1; i <= n; i++) scanf("%lld", a + i);
	build(1, 1, n);
	m= read();
	for(int i= 1; i <= m; i++) {
		tmpx= read(), tmpy= read(), tmpz= read();
		if(tmpy > tmpz) swap(tmpy, tmpz);
		if(tmpx == 1)
			printf("%lld\n", query(1, 1, n, tmpy, tmpz));
		else
			update(1, 1, n, tmpy, tmpz);
	}
	return 0;
}