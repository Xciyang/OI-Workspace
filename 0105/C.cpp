#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <queue>
using namespace std;
int n, r, tmpx;
double h, a[4], ans1, ans2;
int main() {
	cin >> n >> r;
	a[0] = a[1] = a[2] = a[3] = r;
	for(int i = 1; i <= n; i++) {
		cin >> tmpx >> h;
		a[tmpx / 90] = min(a[tmpx / 90], h);
	}
	for(int i = 0; i < 4; i++) {
	}
	return 0;
}