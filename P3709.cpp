#include <iostream>
#include <stdio.h>
#include <map>
#include <math.h>
#include <algorithm>
using namespace std;
int read() {
	int x= 0, f= 1;
	char ch= getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') x= x * 10 + ch - '0', ch= getchar();
	return x * f;
}
inline void write(int x) {
	if(x < 0) x= -x, putchar('-');
	if(x > 9) write(x / 10);
	putchar('0' + x % 10);
	return;
}
int n, m, a[200001], mapptr, cnt[200001], cntt[200001], nowans, ans[200001], ns;
map< int, int > mapping;
struct QUERY {
	int id, l, r, bl;
	int operator<(const QUERY &q2) const {
		return bl == q2.bl ? r < q2.r : l < q2.l;
	}
} qs[200001];
inline void add(int x) {
	--cntt[cnt[x]];
	++cntt[++cnt[x]];
	nowans= max(nowans, cnt[x]);
	return;
}
inline void del(int x) {
	--cntt[cnt[x]];
	if(!cntt[cnt[x]] && nowans == cnt[x]) --nowans;
	++cntt[--cnt[x]];
	return;
}
int main() {
	n= read(), m= read(), ns= sqrt(n);
	for(int i= 1; i <= n; i++) {
		a[i]= read();
		if(!mapping[a[i]]) mapping[a[i]]= ++mapptr;
		a[i]= mapping[a[i]];
	}
	for(int i= 1; i <= m; i++) qs[i].l= read(), qs[i].r= read(), qs[i].id= i, qs[i].bl= (qs[i].l - 1) / ns;
	sort(qs + 1, qs + m + 1);
	int l= 1, r= 0;
	for(int i= 1; i <= m; i++) {
		while(l < qs[i].l) del(a[l++]);
		while(l > qs[i].l) add(a[--l]);
		while(r > qs[i].r) del(a[r--]);
		while(r < qs[i].r) add(a[++r]);
		ans[qs[i].id]= nowans;
	}
	for(int i= 1; i <= m; i++) write(-ans[i]), putchar('\n');
	return 0;
}