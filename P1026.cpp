#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int p, k, s, w[405], len[7], a[405], f[205][45];
char tmps[405], zd[7][205];
int main() {
	cin >> p >> k;
	for(int i= 0; i < p; i++) cin >> (tmps + i * 20 + 1);
	p*= 20;
	memset(w, 0x3f, sizeof(w));
	cin >> s;
	for(int i= 1; i <= s; i++) {
		cin >> zd[i], len[i]= strlen(zd[i]);
		char *st= strstr(tmps + 1, zd[i]);
		while(st) {
			w[st - tmps]= min(w[st - tmps], len[i]);
			st= strstr(st + 1, zd[i]);
		}
	}
	for(int l= 1; l <= k; l++) {
		for(int i= l; i <= p; i++) {
			f[i][l]= max(f[i][l], f[i - 1][l - 1]);
			if(w[i] != 0x3f3f3f3f) {
				for(int j= max(i + w[i] - 1, i + 1); j <= p; j++) f[j][l]= max(f[j][l], f[i][l]) + 1;
				if(w[i] == 1) ++f[i][l];
			}
		}
	}
	cout << f[p][k] << endl;
	return 0;
}