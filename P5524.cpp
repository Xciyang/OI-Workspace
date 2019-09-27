#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
int n, m, a[200005], tmpx, tmpy, tmpz;
long long lazyz[800005];
double cosx[800005], sinx[800005];
inline void build(int nown, int l, int r) {
	if(l == r) {
		cosx[nown]= cos(a[l]), sinx[nown]= sin(a[l]);
		return;
	}
	int mid= (l + r) >> 1;
	build(nown << 1, l, mid), build(nown << 1 | 1, mid + 1, r);
	cosx[nown]= cosx[nown << 1] + cosx[nown << 1 | 1], sinx[nown]= sinx[nown << 1] + sinx[nown << 1 | 1];
	return;
}
inline void Chage(double &c, double &s, long long w) {
	double lc= c, ls= s, wc= cos(w), ws= sin(w);
	c= lc * wc - ls * ws, s= lc * ws + ls * wc;
	return;
}
inline void pd(int nown) {
	Chage(cosx[nown << 1], sinx[nown << 1], lazyz[nown]);
	Chage(cosx[nown << 1 | 1], sinx[nown << 1 | 1], lazyz[nown]);
	lazyz[nown << 1]+= lazyz[nown], lazyz[nown << 1 | 1]+= lazyz[nown], lazyz[nown]= 0;
	return;
}
inline void update(int nown, int l, int r, int ml, int mr, int c) {
	if(ml <= l && r <= mr) {
		Chage(cosx[nown], sinx[nown], c), lazyz[nown]+= c;
		return;
	}
	if(lazyz[nown]) pd(nown);
	int mid= (l + r) >> 1;
	if(mid >= ml) update(nown << 1, l, mid, ml, mr, c);
	if(mid < mr) update(nown << 1 | 1, mid + 1, r, ml, mr, c);
	cosx[nown]= cosx[nown << 1] + cosx[nown << 1 | 1], sinx[nown]= sinx[nown << 1] + sinx[nown << 1 | 1];
	return;
}
inline double query(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) return sinx[nown];
	if(lazyz[nown]) pd(nown);
	int mid= (l + r) >> 1;
	double res= 0;
	if(mid >= ml) res+= query(nown << 1, l, mid, ml, mr);
	if(mid < mr) res+= query(nown << 1 | 1, mid + 1, r, ml, mr);
	return res;
}
int main() {
	scanf("%d", &n);
	for(int i= 1; i <= n; i++) scanf("%d", a + i);
	build(1, 1, n);
	scanf("%d", &m);
	for(int i= 1; i <= m; i++) {
		scanf("%d", &tmpx);
		if(tmpx == 1) {
			scanf("%d%d%d", &tmpx, &tmpy, &tmpz);
			update(1, 1, n, tmpx, tmpy, tmpz);
		}
		else {
			scanf("%d%d", &tmpx, &tmpy);
			printf("%.1lf\n", query(1, 1, n, tmpx, tmpy));
		}
	}
	return 0;
}