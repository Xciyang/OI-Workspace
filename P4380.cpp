#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
int n, m, tmpx, tmpy, tmpz;
struct EDGE {
	int x, y;
};
vector< EDGE > edg[100005];
void dfs(int nown) {
	for(int i= 0, to; i < edg[nown].size(); i++) {
		to= edg[nown][i].x;
	}
	return;
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		edg[tmpy].push_back(EDGE{tmpx, tmpz});
		edg[tmpx].push_back(EDGE{tmpy, tmpz});
	}
	return 0;
}