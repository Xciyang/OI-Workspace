#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, f[55][55];
char tmps[55];
int main() {
	cin >> (tmps + 1), n= strlen(tmps + 1);
	memset(f, 0x3f, sizeof(f));
	for(int i= 1; i <= n; i++) f[i][i]= 1;
	for(int i= 2; i <= n; i++) {
		for(int l= 1, r= l + i - 1; r <= n; l++, r++) {
			for(int j= l; j < r; j++) f[l][r]= min(f[l][r], f[l][j] + f[j + 1][r]);
			if(tmps[l] == tmps[r]) --f[l][r];
		}
	}
	cout << f[1][n] << endl;
	return 0;
}