#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, cnt;
char tmps[51];
long long tmpx, base[51];
int main() {
	cin >> n >> m;
	for(int i= 0; i < m; i++) {
		cin >> tmps, tmpx= 0;
		for(int j= 0; j < n; j++) tmpx= tmpx + (tmps[j] == 'O') * (1ll << j);
		for(int j= 50; j > -1; j--) {
			if(tmpx & (1ll << j)) {
				if(!base[j]) ++cnt, base[j]= tmpx;
				tmpx^= base[j];
			}
		}
	}
	cout << (1ll << cnt) % 2008 << endl;
	return 0;
}