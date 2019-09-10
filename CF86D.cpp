#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
int n, m, a[200001], ns, c[2000001];
long long nowans, ans[200001];
struct QUERY {
	int l, r, lb, id;
	int operator<(const QUERY &q2) const {
		return lb == q2.lb ? r < q2.r : l < q2.l;
	}
} qs[200001];
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
inline void write(register long long x) {
	if(!x) putchar('0');
	if(x < 0) x= -x, putchar('-');
	static int sta[25];
	int tot= 0;
	while(x) sta[tot++]= x % 10, x/= 10;
	while(tot) putchar(sta[--tot] + 48);
}
inline void update(int x, int u) {
	nowans-= c[x] * c[x] * x;
	c[x]+= u;
	nowans+= c[x] * c[x] * x;
}
int main() {
	n= read(), m= read(), ns= sqrt(n);
	for(int i= 1; i <= n; i++) a[i]= read();
	for(int i= 1; i <= m; i++) qs[i].l= read(), qs[i].r= read(), qs[i].id= i, qs[i].lb= (qs[i].l - 1) / ns;
	sort(qs + 1, qs + m + 1);
	int l= 1, r= 0;
	for(int i= 1; i <= m; i++) {
		while(l < qs[i].l) update(a[l++], -1);
		while(l > qs[i].l) update(a[--l], 1);
		while(r < qs[i].r) update(a[++r], 1);
		while(r > qs[i].r) update(a[r--], -1);
		ans[qs[i].id]= nowans;
	}
	for(int i= 1; i <= m; i++) write(ans[i]), putchar('\n');
	return 0;
}