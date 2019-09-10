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
int n, m, a[100001], c[100001], ans[100001][2], ns, cnt[100001], bits[100001], bits2[100001];
struct QUERY {
	int l, r, tmpa, tmpb, lb, id;
	int operator<(const QUERY &Q2) const {
		return lb == Q2.lb ? r < Q2.r : l < Q2.l;
	}
} qs[100001];
#define lowb(a) ((a) & -(a))
inline void update(int x, int c) {
	for(int i= x; i <= n; i+= lowb(i)) bits[i]+= c;
	if(c > 0 && !cnt[x])
		for(int i= x; i <= n; i+= lowb(i)) bits2[i]+= c;
	cnt[x]+= c;
	if(c < 0 && !cnt[x])
		for(int i= x; i <= n; i+= lowb(i)) bits2[i]+= c;
	return;
}
int ans1, ans2;
inline void query(int a, int b) {
	ans1= ans2= 0;
	for(int i= b; i; i-= lowb(i)) ans1+= bits[i], ans2+= bits2[i];
	for(int i= a - 1; i; i-= lowb(i)) ans1-= bits[i], ans2-= bits2[i];
	return;
}
int main() {
	n= read(), m= read(), ns= sqrt(n);
	for(int i= 1; i <= n; i++) a[i]= read();
	for(int i= 1; i <= m; i++) qs[i].l= read(), qs[i].r= read(), qs[i].tmpa= read(), qs[i].tmpb= read(), qs[i].id= i, qs[i].lb= (qs[i].l - 1) / ns;
	int l= 1, r= 0;
	sort(qs + 1, qs + m + 1);
	for(int i= 1; i <= m; i++) {
		while(l < qs[i].l) update(a[l++], -1);
		while(l > qs[i].l) update(a[--l], 1);
		while(r < qs[i].r) update(a[++r], 1);
		while(r > qs[i].r) update(a[r--], -1);
		query(qs[i].tmpa, qs[i].tmpb);
		ans[qs[i].id][0]= ans1, ans[qs[i].id][1]= ans2;
	}
	for(int i= 1; i <= m; i++) write(ans[i][0]), putchar(' '), write(ans[i][1]), putchar('\n');
	return 0;
}