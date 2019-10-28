#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <queue>
#include <math.h>
using namespace std;
double a, b, x, r2, S2, ans, S2_1;
double change(double x) {
	return x * 180 / 3.1415926535898;
}
int main() {
	cin >> a >> b >> x;
	r2= a * a;
	S2= r2 * b;
	S2_1= S2 / 2;
	if(x > S2_1) {
		double res= (x - b * a * a / 2) * 2 / a / a;
		// printf("%lf,%lf", (res + b) * a * a / 2, x);
		double res2= atan(fabs(res - b) / a);
		ans= change(res2);
	}
	else if(x < S2_1) {
		double res= 2 * x / a / b;
		// printf("%lf,%lf", res * b * a / 2, x);
		double res2= atan(b / res);
		ans= change(res2);
	}
	else {
		ans= 45;
	}
	printf("%.10lf\n", ans);
	return 0;
}