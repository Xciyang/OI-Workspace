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
inline void write(register int x) {
	if(!x) putchar('0');
	if(x < 0) x= -x, putchar('-');
	static int sta[25];
	int tot= 0;
	while(x) sta[tot++]= x % 10, x/= 10;
	while(tot) putchar(sta[--tot] + 48);
}
int n, m, a[100001], ans[1000001], ns, cnt[100001], bits2[100001];
struct QUERY {
	int l, r, tmpa, tmpb, lb, id;
	int operator<(const QUERY &Q2) const {
		return lb == Q2.lb ? r < Q2.r : l < Q2.l;
	}
} qs[1000001];
#define lowb(a) ((a) & -(a))
inline void add(int x) {
	if(!cnt[x])
		for(int i= x; i <= n; i+= lowb(i)) ++bits2[i];
	++cnt[x];
	return;
}
inline void del(int x) {
	--cnt[x];
	if(!cnt[x])
		for(int i= x; i <= n; i+= lowb(i)) --bits2[i];
	return;
}
inline int query(int a, int b) {
	int ans2= 0;
	for(int i= b; i; i-= lowb(i)) ans2+= bits2[i];
	for(int i= a - 1; i; i-= lowb(i)) ans2-= bits2[i];
	return ans2;
}
int main() {
	n= read(), m= read(), ns= sqrt(n);
	for(int i= 1; i <= n; i++) a[i]= read();
	for(int i= 1; i <= m; i++) qs[i].l= read(), qs[i].r= read(), qs[i].tmpa= read(), qs[i].tmpb= read(), qs[i].id= i, qs[i].lb= (qs[i].l - 1) / ns;
	int l= 1, r= 0;
	sort(qs + 1, qs + m + 1);
	for(int i= 1; i <= m; i++) {
		while(l < qs[i].l) del(a[l++]);
		while(l > qs[i].l) add(a[--l]);
		while(r < qs[i].r) add(a[++r]);
		while(r > qs[i].r) del(a[r--]);
		ans[qs[i].id]= query(qs[i].tmpa, qs[i].tmpb);
	}
	for(int i= 1; i <= m; i++) write(ans[i]), putchar('\n');
	return 0;
}