#include <iostream>
#include <stdio.h>
#include <limits.h>
using namespace std;
#define int long long
int n, m, tmpx, num[32][2];
char tmps[4];
int ans= -1;
void dfs(int nown, int total, int tmpans) {
	if(total > m || tmpans <= ans) return;
	if(nown == -1) {
		ans= tmpans;
		return;
	}
	dfs(nown - 1, total, tmpans + (num[nown][0] << nown));
	dfs(nown - 1, total + (1 << nown), tmpans + (num[nown][1] << nown));
	return;
}
signed main() {
	cin >> n >> m;
	for(int i= 0; i < 31; i++) num[i][1]= 1;
	for(int i= 0; i < n; i++) {
		cin >> tmps >> tmpx;
		for(int j= 0; j < 31; j++) {
			int ch= (tmpx >> j) & 1;
			if(tmps[0] == 'A')
				num[j][0]&= ch, num[j][1]&= ch;
			else if(tmps[0] == 'O')
				num[j][0]|= ch, num[j][1]|= ch;
			else
				num[j][0]^= ch, num[j][1]^= ch;
		}
	}
	dfs(30, 0, 0);
	cout << ans << endl;
	return 0;
}