#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <queue>
#include <math.h>
using namespace std;
int n, m, tmpx, tmpy, r[606], yr[606];
double f[606][606], ans= 1e15;
vector< int > edg[606];
queue< int > qu;
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(tmpy);
		++r[tmpy];
	}
	qu.push(1);
	int nown, to;
	f[1][0]= 1;
	while(!qu.empty()) {
		nown= qu.front(), qu.pop();
		for(int i= 0; i < edg[nown].size(); i++) {
			to= edg[nown][i];
			for(int j= 1; j <= n; j++) f[to][j]+= f[nown][j - 1] / (double)edg[nown].size();
			if(++yr[to] == r[to]) qu.push(to);
		}
		double res= 0;
		for(int j= 1; j <= n; j++) res+= f[n][j] * j;
		ans= min(ans, res);
	}
	for(int k= 0; k < edg[nown].size(); k++) {
		++yr[edg[nown][k]];
		for(int i= 1; i <= n; i++) {
			for(int j= 1; j <= n; i++) f[i][j]= 0;
			yr[i]= 0;
		}
		f[1][0]= 1;
		qu.push(1);
		while(!qu.empty()) {
			nown= qu.front(), qu.pop();
			for(int i= 0; i < edg[nown].size(); i++) {
				if(i == k) continue;
				to= edg[nown][i];
				for(int j= 1; j <= n; j++) f[to][j]+= f[nown][j - 1] / (double)edg[nown].size();
				if(++yr[to] == r[to]) qu.push(to);
			}
		}
		double res= 0;
		for(int j= 1; j <= 600; j++) res+= f[n][j] * j;
		ans= min(ans, res);
	}
	cout << ans << endl;
	return 0;
}