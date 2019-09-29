#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
int n, s, a[55], aptr, q, h, f[55][365];
char tmps[55];
int zx= 360;
inline int abs(int x) {
	return x < 0 ? -x : x;
}
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) {
		cin >> tmps >> s;
		if(tmps[0] == 'r')
			a[++aptr]= s;
		else if(tmps[0] == 'l')
			a[++aptr]= -s;
		else if(tmps[0] == 'f')
			q+= s;
		else
			h+= s;
	}
	f[0][0]= 1;
	for(int i= 1; i <= aptr; i++) {
		for(int j= 0; j <= 360; j++) {
			f[i][j]= max(f[i][j], f[i - 1][j]);
			f[i][j]= max(f[i][j], f[i - 1][(j + a[i] + 360) % 360]);
		}
	}
	for(int i= 0; i <= 360; i++) {
		if(f[aptr][i] && abs(i - 180) < zx) zx= abs(i - 180);
	}
	printf("%.6lf\n", sqrt((double)q * q + (double)h * h + (double)2 * q * h * cos(zx * 3.1415926535 / 180)));
	return 0;
}