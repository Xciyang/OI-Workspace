#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
int n, m, a[1000010], cnt[1000010], ans, blen, answ[1000010];
struct DATA {
	int id, l, r;
} datas[1000010];
inline int cmpbid(const DATA &d1, const DATA &d2) {
	return d1.l / blen == d2.l / blen ? d1.r < d2.r : d1.l < d2.l;
}
inline void del(int c) {
	if((--cnt[c]) == 0 && c < ans) ans= c;
	return;
}
inline void add(int c) {
	if((++cnt[c]) == 1 && ans == c)
		while(cnt[ans]) ++ans;
	return;
}
int main() {
	scanf("%d%d", &n, &m), blen= pow(m, 0.6);
	for(register int i= 1; i <= n; i++) scanf("%d", a + i);
	for(register int i= 1; i <= m; i++) datas[i].id= i, scanf("%d%d", &datas[i].l, &datas[i].r);
	sort(datas + 1, datas + m + 1, cmpbid);
	register int l= 1, r= 0;
	for(register int i= 1; i <= m; i++) {
		while(l < datas[i].l) del(a[l++]);
		while(l > datas[i].l) add(a[--l]);
		while(r > datas[i].r) del(a[r--]);
		while(r < datas[i].r) add(a[++r]);
		answ[datas[i].id]= ans;
	}
	for(register int i= 1; i <= m; i++) printf("%d\n", answ[i]);
	return 0;
}