#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m, nn, edge[16][16], tmpx, tmpy, tmpz, sums;
int blocks[1 << 16], len, f[1 << 16][16];
int main() {
	cin >> n >> m;
	nn= 1 << n;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		sums+= edge[tmpx][tmpy]= edge[tmpy][tmpx]= tmpz;
	}
	for(int i= 0; i < nn; i++) {
		for(int j= 1; j <= n; j++) {
			if(!(i & (1 << (j - 1))) && !(blocks[i | (1 << (j - 1))])) {
				blocks[i | (1 << (j - 1))]= blocks[i];
				for(int k= 1; k <= n; k++)
					if((i & (1 << (k - 1)))) blocks[i | (1 << (j - 1))]+= edge[j][k];
			}
		}
	}
	memset(f, -1, sizeof(f));
	f[1][1]= 0;
	for(int i= 0; i < nn; i++) {
		for(int j= 1; j <= n; j++) {
			if(f[i][j] != -1 && (i & (1 << (j - 1)))) {
				for(int k= 1; k <= n; k++)
					if(!(i & (1 << (k - 1))) && edge[j][k]) f[i | (1 << (k - 1))][k]= max(f[i | (1 << (k - 1))][k], f[i][j] + edge[j][k]);
				tmpx= ((nn - 1) ^ i) | (1 << (j - 1));
				for(int k= tmpx; k; k= (k - 1) & tmpx)
					if(k & (1 << (j - 1))) f[i | k][j]= max(f[i | k][j], f[i][j] + blocks[k]);
			}
		}
	}
	cout << sums - f[nn - 1][n] << endl;
	return 0;
}