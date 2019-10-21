#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
int n, m, k, ans[10003][10003], tmpx;
int main() {
	cin >> n >> m >> k;
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) {
			cin >> tmpx;
			if(!ans[tmpx][j]) ++ans[tmpx][0];
			ans[tmpx][j]= 1;
		}
	}
	for(int i= 1; i <= k; i++) cout << ans[i][0] << ' ';
	cout << endl;
	return 0;
}