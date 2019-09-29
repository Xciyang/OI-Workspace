#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
int n, m, tmpx, tmpy, r[100005], dep[100005];
vector< int > edg[100005];
queue< int > qu;
int main() {
	cin >> n >> m;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(tmpy), ++r[tmpy];
	}
	for(int i= 1; i <= n; i++)
		if(!r[i]) qu.push(i), dep[i]= 1;
	register int nown;
	while(!qu.empty()) {
		nown= qu.front(), qu.pop();
		for(int i= 0, to; i < edg[nown].size(); i++) {
			to= edg[nown][i], dep[to]= max(dep[to], dep[nown] + 1);
			if(!--r[to]) qu.push(to);
		}
	}
	for(int i= 1; i <= n; i++) cout << dep[i] << endl;
	return 0;
}