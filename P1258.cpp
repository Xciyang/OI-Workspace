#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
double s, a, b;
double calc1(double jia) {
	return jia / b + (s - jia) / a;
}
double calc2(double jia) {
	return jia / b + (jia - a * jia / b) / (a + b) + (s - (jia - a * jia / b) / (a + b) * a - jia / b * a) / b;
}
int main() {
	cin >> s >> a >> b;
	double l= 1, r= s, mid;
	while(l <= r) {
		mid= (l + r) / 2;
		double j= calc1(mid), y= calc2(mid);
		if(j < y)
			r= mid;
		else
			l= mid;
		if(fabs(j - y) < 1e-6) {
			printf("%.6lf\n", j);
			break;
		}
	}
	return 0;
}