#include <iostream>
#include <stdio.h>
using namespace std;
struct NODE {
	double x, y;
} a[7005];
int n, m, k, fa[7005];
inline int getf(int x) {
	return fa[x] == x ? x : fa[x]= getf(fa[x]);
}
inline int check(double x) {
	for(int i= 1; i <= k; i++) fa[i]= i;
	for(int i= 1; i <= k; i++) {
		for(int j= 1; j <= k; j++) {
			if(getf(i) == getf(j)) continue;
			if((a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y) < x * x * 4) {
				fa[getf(i)]= getf(j);
			}
		}
	}
	for(int i= 1; i <= k; i++) {
		for(int j= 1; j <= k; j++) {
			if(m - a[i].y < x * 2 && a[j].y < x * 2) {
				if(getf(i) == getf(j)) return 1;
			}
		}
	}
	return 0;
}
int main() {
	cin >> n >> m >> k;
	for(int i= 1; i <= k; i++) cin >> a[i].x >> a[i].y;
	double l= 0, r= (double)m / 2, mid;
	while(l < r - 1e-9) {
		mid= (l + r) / 2;
		if(check(mid))
			r= mid;
		else
			l= mid;
	}
	printf("%.8lf\n", l);
	return 0;
}