#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
int n, p, u[105], b[105], tmpx, tmpy, tmpz, r[105], yr[105], c[105], wp[105], ans[105], aptr;
struct EDGE {
	int to, w;
};
vector< EDGE > edg[105];
queue< int > qu;
int main() {
	cin >> n >> p;
	for(int i= 1; i <= n; i++) cin >> b[i] >> u[i];
	for(int i= 1; i <= p; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		edg[tmpx].push_back(EDGE{tmpy, tmpz}), ++r[tmpy], ++c[tmpx];
	}
	for(int i= 1; i <= n; i++)
		if(!r[i]) qu.push(i), wp[i]= 1;
	register int nown;
	while(!qu.empty()) {
		nown= qu.front(), qu.pop();
		if(yr[nown] != r[nown]) {
			wp[nown]= 0;
			continue;
		}
		if(r[nown]) b[nown]-= u[nown];
		if(b[nown] <= 0) continue;
		for(int i= 0; i < edg[nown].size(); i++) {
			b[edg[nown][i].to]+= edg[nown][i].w * b[nown], ++yr[edg[nown][i].to];
			if(!wp[edg[nown][i].to]) wp[edg[nown][i].to]= 1, qu.push(edg[nown][i].to);
		}
	}
	for(int i= 1; i <= n; i++)
		if(!c[i] && b[i] > 0) ans[++aptr]= i;
	if(!aptr)
		cout << "NULL" << endl;
	else
		for(int i= 1; i <= aptr; i++) cout << ans[i] << ' ' << b[ans[i]] << endl;
	return 0;
}