#include <iostream>
#include <stdio.h>
using namespace std;
int n, bx, by, tmp[105][105], maxans;
int lefts[105][105], rights[105][105], ups[105][105], downs[105][105], walkpast[105][105];
void dfs(int x, int y, int ans) {
	walkpast[x][y]= 1;
	if(ups[x][y] && ups[x][y] != x - 1 && !walkpast[ups[x][y]][y]) dfs(ups[x][y], y, ans + x - ups[x][y]);
	if(downs[x][y]&& downs[x][y] != x + 1 && !walkpast[downs[x][y]][y]) dfs(downs[x][y], y, ans + downs[x][y] - x);
	if(lefts[x][y]&& lefts[x][y] != y - 1 && !walkpast[x][lefts[x][y]]) dfs(x, lefts[x][y], ans + y - lefts[x][y]);
	if(rights[x][y]&& rights[x][y] != y + 1 && !walkpast[x][rights[x][y]]) dfs(x, rights[x][y], ans + rights[x][y] - y);
	maxans= max(maxans, ans);
	return;
}
int main() {
	cin >> n >> bx >> by;
	for(int i= 1; i <= n; i++)
		for(int j= 1; j <= n; j++) cin >> tmp[i][j];
	for(int i= 1; i <= n; i++) {
		for(int j= 1, k= 0, k2= 0; j <= n; j++) {
			lefts[i][j]= k, ups[j][i]= k2;
			if(tmp[i][j] == 0) k= j;
			if(tmp[j][i] == 0) k2= j;
		}
		for(int j= n, k= 0, k2= 0; j; j--) {
			rights[i][j]= k, downs[j][i]= k2;
			if(tmp[i][j] == 0) k= j;
			if(tmp[j][i] == 0) k2= j;
		}
	}
	dfs(bx, by, 0);
	cout << maxans << endl;
	return 0;
}