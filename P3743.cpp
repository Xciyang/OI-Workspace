#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
int n;
double p, a[100005], b[100005], bb[100005];
int judge(double x) {
	memcpy(bb, b, sizeof(b));
	double c= x * p;
	for(int i= 1; i <= n; i++) {
		if((double)bb[i] / a[i] >= x) continue;
		c-= x * a[i] - bb[i];
		if(c < 0) return 0;
	}
	return 1;
}
int main() {
	cin >> n >> p;
	double sum;
	for(int i= 1; i <= n; i++) cin >> a[i] >> b[i], sum+= a[i];
	if(sum <= p) {
		cout << -1 << endl;
		return 0;
	}
	double l= 0, r= 1e10, mid;
	while(l + 1e-6 < r) {
		mid= (l + r) / 2;
		if(judge(mid))
			l= mid;
		else
			r= mid;
	}
	cout << l << endl;
	return 0;
}