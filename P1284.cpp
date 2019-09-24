#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
int n, a[45], f[1005][1005], sum, hsum;
inline int judge(int x, int y, int z) {
	return x + y > z && x + z > y && y + z > x;
}
inline double S(int x, int y, int z) {
	double p= (double)(x + y + z) / 2;
	return p * (p - x) * (p - y) * (p - z);
}
double maxa= -1;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i], sum+= a[i];
	f[0][0]= 1;
	for(int i= 1; i <= n; i++) {
		for(int j= 1000; j >= 0; j--) {
			for(int k= 1000; k >= 0; k--) {
				if(j >= a[i] && f[j - a[i]][k]) f[j][k]= 1;
				if(k >= a[i] && f[j][k - a[i]]) f[j][k]= 1;
			}
		}
	}
	for(int i= 1; i <= 1000; i++) {
		for(int j= 1; j <= 1000; j++) {
			if(!f[i][j] || !judge(i, j, sum - i - j)) continue;
			maxa= max(maxa, S(i, j, sum - i - j));
		}
	}
	if(maxa == -1) {
		cout << -1 << endl;
		return 0;
	}
	printf("%d\n", int(sqrt(maxa) * 100));
	return 0;
}