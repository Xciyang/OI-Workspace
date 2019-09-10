#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
int n, m, blen, col[50001], mark[1000001], ans, p1, p2, anss[50001], nl= 1, nr, upq;
char tmpc[3];
int read() {
	int e= 0, f= 1;
	char ch= getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') e= e * 10 + ch - '0', ch= getchar();
	return e * f;
}
int put(const int &i) {
	if(i > 9) put(i / 10);
	return putchar('0' + i % 10);
}
struct DATA {
	int l, r, id, lastq, bid;
} queryd[50001], changed[50001];
inline int cmpbid(const DATA &d1, const DATA &d2) {
	return d1.bid == d2.bid ? d1.r < d2.r : d1.l < d2.l;
}
void change(int nid) {
	if(changed[nid].id >= nl && changed[nid].id <= nr) {
		ans+= (++mark[changed[nid].bid] == 1), ans-= (--mark[col[changed[nid].id]] == 0);
	}
	swap(changed[nid].bid, col[changed[nid].id]);
	return;
}
int main() {
	n= read(), m= read();
	for(int i= 1; i <= n; i++) col[i]= read();
	for(int i= 1; i <= m; i++) {
		scanf("%s", tmpc);
		if(tmpc[0] == 'Q') {
			++p1, queryd[p1].id= p1, queryd[p1].lastq= p2;
			queryd[p1].l= read(), queryd[p1].r= read();
		}
		else {
			changed[++p2].id= read(), changed[p2].bid= read();
		}
	}
	blen= ceil(exp((log(n) + log(p1)) / 3));
	for(int i= 1; i <= p1; i++) queryd[i].bid= i / blen + 1;
	sort(queryd + 1, queryd + p1 + 1, cmpbid);
	for(int i= 1; i <= p1; i++) {
		while(nl < queryd[i].l) ans-= (--mark[col[nl++]] == 0);
		while(nl > queryd[i].l) ans+= (++mark[col[--nl]] == 1);
		while(nr < queryd[i].r) ans+= (++mark[col[++nr]] == 1);
		while(nr > queryd[i].r) ans-= (--mark[col[nr--]] == 0);
		while(upq < queryd[i].lastq) change(++upq);
		while(upq > queryd[i].lastq) change(upq--);
		anss[queryd[i].id]= ans;
	}
	for(int i= 1; i <= p1; i++) put(anss[i]), putchar('\n');
	return 0;
}