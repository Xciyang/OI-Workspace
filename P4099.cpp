#include <iostream>
#include <stdio.h>
#include <list>
#include <vector>
#include <queue>
using namespace std;
const int mod= 1000000007;
int T, n, r[1004], tmpx, tmpy, ans, yr[1004], nyr[1004], wp[1004], frac[1004];
vector< int > edg[1004];
char tmpc;
queue< int > qu, nqu;
int main() {
	frac[0]= 1;
	for(int i= 1; i <= 1000; i++) frac[i]= (long long)frac[i - 1] * i % mod;
	cin >> T;
	while(T--) {
		cin >> n;
		for(int i= 1; i <= n; i++) edg[i].clear(), r[i]= yr[i]= 0;
		for(int i= 1; i < n; i++) {
			cin >> tmpx >> tmpc >> tmpy, ++tmpx, ++tmpy;
			if(tmpc == '>') swap(tmpx, tmpy);
			edg[tmpx].push_back(tmpy), ++r[tmpy];
		}
		for(int i= 1; i <= n; i++)
			if(r[i] == 0) qu.push(i);
		ans= frac[qu.size()];
		register int nown;
		while(true) {
			while(!qu.empty()) {
				nown= qu.front(), qu.pop();
				for(int i= 0; i < edg[nown].size(); i++)
					if(++yr[edg[nown][i]] == r[edg[nown][i]]) nqu.push(edg[nown][i]);
			}
			if(nqu.empty()) break;
			ans= (long long)ans * frac[nqu.size()] % mod;
			swap(qu, nqu);
		}
		cout << ans << endl;
	}
	return 0;
}