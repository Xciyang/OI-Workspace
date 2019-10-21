#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <time.h>
using namespace std;
int n, col[300005], fa[300005], siz[300005], tmpx, tmpy;
vector< int > edg[300005];
struct CMP {
	inline int operator()(const int &a1, const int &a2) const {
		return siz[a1] < siz[a2];
	}
};
priority_queue< int, vector< int >, CMP > edg2[300005];
priority_queue< int, vector< int >, CMP > edgs;

void dfs(int nown) {
	siz[nown]= 1;
	for(int i= 0; i < (int)edg[nown].size(); i++)
		if(edg[nown][i] != fa[nown]) {
			++siz[nown];
			fa[edg[nown][i]]= nown, dfs(edg[nown][i]), edg2[nown].push(edg[nown][i]);
		}
	return;
}
int times[300005], ans[300005];
void dfs2(int nown) {
	if(++times[nown] == 1) ans[++ans[0]]= nown;
	int flag= 0;
	while(nown && edg2[nown].empty()) {
		if(++times[nown] == 1) ans[++ans[0]]= nown;
		nown= fa[nown], ++flag;
	}
	if(!nown || edg2[nown].empty()) return;
	int x= edg2[nown].top(), y;
	edg2[nown].pop();
	if(flag < 2 && siz[x] > 1) {
		--siz[x], edg2[nown].push(x);
		y= edg2[x].top(), edg2[x].pop();
		dfs2(y);
	}
	else {
		dfs2(x);
	}
}
int main() {
	srand(time(0));
	cin >> n;
	for(int i= 1; i < n; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(tmpy), edg[tmpy].push_back(tmpx);
	}
	dfs(1);
	dfs2(1);
	cout << "Yes" << endl;
	for(int i= 1; i <= ans[0]; i++) cout << ans[i] << ' ';
	return 0;
}
/*
7
1 2
1 3
1 4
1 5
1 6
6 7

*/

/*
8
1 2
2 3
3 4
4 5
4 6
4 7
7 8

*/