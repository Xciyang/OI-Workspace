#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, f[2][10];
int main() {
	cin >> n;
	f[0][1]= 1;
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= 8; j++) {
			f[i & 1][j]= 0;
			if((j + 6) % 8 + 1 != 5) f[i & 1][j]= (f[i & 1][j] + f[(i & 1) ^ 1][(j + 6) % 8 + 1]) % 1000;
			if(j % 8 + 1 != 5) f[i & 1][j]= (f[i & 1][j] + f[(i & 1) ^ 1][j % 8 + 1]) % 1000;
		}
	}
	cout << f[n & 1][5] << endl;
	return 0;
}