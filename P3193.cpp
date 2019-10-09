#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
char tmpc;
int n, m, k, tmpx;
struct MAT {
	int a[25][15];
	MAT operator*(const MAT &m2) const {
		MAT res;
		memset(&res, 0, sizeof(res));
		for(int i= 1; i <= m; i++) {
            for(int j= 1)
		}
	}
} base, ans;
int main() {
	cin >> n >> m >> k;
	for(int i= 1; i <= m; i++) {
		cin >> tmpc;
		base[i][tmpc - '0' + 1]= 1;
	}
	return 0;
}