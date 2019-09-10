#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
int n, m, k, col[50001], blocklen;
long long ans, mark[50001], tmpx;
struct WZ {
	int id, blockid, l, r;
	long long ansz;
} wzs[50001];
inline bool cmpbid(const WZ &w1, const WZ &w2) {
	return w1.blockid == w2.blockid ? w1.r < w2.r : w1.l < w2.l;
}
inline bool cmpid(const WZ &w1, const WZ &w2) {
	return w1.id < w2.id;
}
inline void updateAns(int ii, int c) {
	ans-= mark[col[ii]] * mark[col[ii]];
	mark[col[ii]]+= c;
	ans+= mark[col[ii]] * mark[col[ii]];
	return;
}
inline int read() {
	int f= 1, x= 0;
	char ch= getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') x= x * 10 + ch - '0', ch= getchar();
	return x * f;
}
int main() {
	n= read(), m= read(), k= read(), blocklen= sqrt(n);
	for(int i= 1; i <= n; i++) col[i]= read();
	for(int i= 1; i <= m; i++) {
		wzs[i].l= read(), wzs[i].r= read();
		wzs[i].id= i, wzs[i].blockid= (i - 1) / blocklen + 1;
	}
	sort(wzs + 1, wzs + m + 1, cmpbid);
	int l= 1, r= 0;
	for(int i= 1; i <= m; i++) {
		while(l < wzs[i].l) updateAns(l++, -1);
		while(l > wzs[i].l) updateAns(--l, 1);
		while(r < wzs[i].r) updateAns(++r, 1);
		while(r > wzs[i].r) updateAns(r--, -1);
		wzs[i].ansz= ans;
	}
	sort(wzs + 1, wzs + m + 1, cmpid);
	for(int i= 1; i <= m; i++) printf("%lld\n", wzs[i].ansz);
	return 0;
}