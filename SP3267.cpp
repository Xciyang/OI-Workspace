#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
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
inline void write(register long long x) {
	if(!x) putchar('0');
	if(x < 0) x= -x, putchar('-');
	static int sta[25];
	int tot= 0;
	while(x) sta[tot++]= x % 10, x/= 10;
	while(tot) putchar(sta[--tot] + 48);
}
int n, a[30001], q, cnt[1000006], ns, nowans, ans[200001];
struct QUERY {
	int l, r, id, lb;
	int operator<(const QUERY &Q2) const {
		return lb == Q2.lb ? r < Q2.r : l < Q2.l;
	}
} qs[200001];
inline void add(int x) {
	if(!cnt[x]) ++nowans;
	++cnt[x];
	return;
}
inline void del(int x) {
	--cnt[x];
	if(!cnt[x]) --nowans;
	return;
}
int main() {
	n= read(), ns= sqrt(n);
	for(int i= 1; i <= n; i++) a[i]= read();
	q= read();
	for(int i= 1; i <= q; i++) qs[i].l= read(), qs[i].r= read(), qs[i].id= i, qs[i].lb= (qs[i].l - 1) / ns;
	sort(qs + 1, qs + q + 1);
	int l= 1, r= 0;
	for(int i= 1; i <= q; i++) {
		while(l < qs[i].l) del(a[l++]);
		while(l > qs[i].l) add(a[--l]);
		while(r < qs[i].r) add(a[++r]);
		while(r > qs[i].r) del(a[r--]);
		ans[qs[i].id]= nowans;
	}
	for(int i= 1; i <= q; i++) write(ans[i]), putchar('\n');
	return 0;
}