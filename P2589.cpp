#include <iostream>
#include <stdio.h>
using namespace std;
int n;
struct BOT {
	int h, r1, r2;
	double k;
} bs[10];
inline double calck(int h, int r1, int r2) {
	return ((double)r2 - r1) / 2 / h;
}
int n, N, t[1 << 10];
double bestans;
double F[1 << 10][10];
int calc(int x) {
	return x ? calc(x - (x & -x)) + 1 : 0;
}
int main() {
	cin >> n, N= (1 << n);
	for(int i= 1; i <= n; i++) {
		cin >> bs[i].h >> bs[i].r1 >> bs[i].r2;
		bs[i].k= calck(bs[i].h, bs[i].r1, bs[i].r2);
	}
	for(int i= 1; i < N; i++) t[i]= calc(i);
	for(int i= 1; i <= n; i++) F[1 << (i - 1)][0]= bs[i].h;
	for(int l= 2; l <= n; l++) {
		for(int s= 1; s < N; s++) {
            if(calc(s) != l) continue;
		}
	}
	return 0;
}