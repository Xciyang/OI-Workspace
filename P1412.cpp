#include <iostream>
#include <stdio.h>
using namespace std;
int n, k, c, w;
int typ[100005], a[100005];
double f[100005];
int main() {
	cin >> n >> k >> c >> w;
	for(int i= 1; i <= n; i++) cin >> typ[i] >> a[i];
	for(int i= n; i; i--) {
		if(typ[i] == 1)
			f[i]= max(f[i + 1], f[i + 1] * (1 - 0.01 * k) + a[i]);
		else
			f[i]= max(f[i + 1], f[i + 1] * (1 + 0.01 * c) - a[i]);
	}
    printf("%.2lf\n", f[1] * w);
	return 0;
}