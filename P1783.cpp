#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
struct EDGE {
	int x, y;
	double dis;
	inline int operator<(EDGE &e2) const {
		return dis < e2.dis;
	}
} e[640005];
int n, m, edptr;
double x[805], y[805];
int f[805];
inline int getf(int x) {
	return f[x] == x ? x : f[x]= getf(f[x]);
}
inline int check(double k) {
	for(int i= 1; i <= m; i++) f[i]= i;
	for(int i= 1; i <= edptr; i++) {
		if(e[i].dis <= k) {
			int tmpx= getf(e[i].x), tmpy= getf(e[i].y);
			if(tmpx == tmpy) continue;
			f[tmpx]= tmpy;
		}
	}
	for(int i= 1; i <= m; i++)
		for(int j= 1; j <= m; j++)
			if(getf(i) == getf(j) && x[i] - k < 0 && x[j] + k > n) return 1;
	return 0;
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= m; i++) cin >> x[i] >> y[i];
	for(int i= 1; i <= m; i++) {
		for(int j= i + 1; j <= m; j++) {
			e[++edptr]= EDGE{i, j, sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])) / 2};
		}
	}
	sort(e + 1, e + edptr + 1);
	double l= 0, r= n, mid, ans;
	while(l + 1e-5 < r) {
		mid= (l + r) / 2;
		if(check(mid))
			r= mid, ans= mid;
		else
			l= mid;
	}
	printf("%.2lf\n", ans);
	return 0;
}