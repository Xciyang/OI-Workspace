#include <iostream>
#include <stdio.h>
#include <limits.h>
using namespace std;
int n, m, k, nn;
int saves[(1 << 13) + 1][101], edg[101][101], ans= INT_MAX, kind[101], tmpx, tmpy, tmpz;
void dfs(int nown, int sta, int cost) {
	if(cost >= ans || (saves[sta][nown] && cost >= saves[sta][nown])) return;
	if(sta == nn) {
		ans= cost;
		return;
	}
	saves[sta][nown]= cost;
	for(int i= 1; i <= n; i++)
		if(edg[nown][i] && ((1 << kind[i]) & sta) == 0) dfs(i, sta | (1 << kind[i]), cost + edg[nown][i]);
	return;
}
int main() {
	cin >> n >> m >> k;
	nn= (1 << k) - 1;
	for(int i= 1; i <= n; i++) cin >> kind[i];
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		edg[tmpx][tmpy]= tmpz;
	}
	for(int i= 1; i <= n; i++) dfs(i, 1 << kind[i], 0);
	if(ans == INT_MAX) {
		cout << "Ushio!" << endl;
        return 0;
	}
	cout << ans << endl;
	return 0;
}

/*


*/