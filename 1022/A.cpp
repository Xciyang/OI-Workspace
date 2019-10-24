#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
int n, m, tmpx, tmpy, wr[25], r[25], ans, col[25];
int c[25];
struct EDGE {
	int from, to;
} edg[25];
int bfs() {
	memcpy(col, c, sizeof(col));
	memset(wr, 0, sizeof(wr));
	int res= 0, flag= 1;
	while(flag) {
		flag= 0;
		for(int i= 0; i < m; i++)
			if(col[i] == 1) ++wr[edg[i].from], ++wr[edg[i].to], col[i]= 2, ++res;
		for(int i= 0; i < m; i++) {
			if(col[i] == 0)
				if(wr[edg[i].from] + 1 == r[edg[i].from] || wr[edg[i].to] + 1 == r[edg[i].to]) flag= col[i]= 1;
		}
	}
	return res == m;
}
void dfs(int nown, int tmpans, int last) {
	if(tmpans >= ans) return;
	if(bfs() && last) {
		ans= tmpans;
		return;
	}
	if(nown == m) return;
	int k= col[nown];
	if(!k) {
		c[nown]= 1;
		dfs(nown + 1, tmpans + 1, 1);
		c[nown]= 0;
		dfs(nown + 1, tmpans, 0);
	}
	else {
		c[nown]= 0;
		dfs(nown + 1, tmpans, 0);
		c[nown]= 1;
		dfs(nown + 1, tmpans + 1, 1);
		c[nown]= 0;
	}
	return;
}
int main() {
	cin >> n >> m;
	for(int i= 0; i < m; i++) {
		cin >> tmpx >> tmpy;
		edg[i]= EDGE{tmpx, tmpy};
		++r[tmpx], ++r[tmpy];
	}
	random_shuffle(edg, edg + m);
	ans= m;
	dfs(0, 0, 0);
	cout << ans << endl;
	return 0;
}