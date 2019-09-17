#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, x[50005], f1[50005], f2[50005];
#define EPS 1e-3
int judge(double k) {
	for(int i= 1; i <= n; i++) {
		int l= i, r= n, mid, ans= i;
		while(l <= r) {
			mid= (l + r) >> 1;
			if(x[mid] > k * 2 + x[i])
				r= mid - 1;
			else
				l= mid + 1, ans= mid;
		}
		if(f1[i] <= k - 1 && f2[ans] <= k - 1) return 1;
	}
	return 0;
}
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> x[i];
	sort(x + 1, x + n + 1);
	n= unique(x + 1, x + n + 1) - x - 1;
	for(int i= 2; i <= n; i++) {
		int l= 1, r= i - 1, mid, ans= i - 1;
		while(l <= r) {
			mid= (l + r) >> 1;
			if(x[i] - x[mid] > f1[mid] + 1)
				l= mid + 1;
			else
				r= mid - 1, ans= mid;
		}
		f1[i]= max(f1[ans] + 1, x[i] - x[ans]);
	}
	for(int i= n - 1; i; i--) {
		int l= i + 1, r= n, mid, ans= i + 1;
		while(l <= r) {
			mid= (l + r) >> 1;
			if(x[mid] - x[i] > f2[mid] + 1)
				r= mid - 1;
			else
				l= mid + 1, ans= mid;
		}
		f2[i]= max(f2[ans] + 1, x[ans] - x[i]);
	}
	double l= 0, r= 1e9, mid;
	while(l < r - EPS) {
		mid= (l + r) / 2;
		if(judge(mid))
			r= mid;
		else
			l= mid;
	}
	printf("%.1lf\n", l);
	return 0;
}