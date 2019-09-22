#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>
#include <queue>
using namespace std;
int T, n, m, tmpx, tmpy, ans[100005], wb[100005], ins[100005], aptr, r[100005], yr[100005];
vector< int > edg[100005];
priority_queue< int > qu;
int main() {
	cin >> T;
	while(T--) {
		cin >> n >> m;
		memset(ins, 0, sizeof(ins)), memset(wb, 0, sizeof(wb)), memset(r, 0, sizeof(r)), memset(yr, 0, sizeof(yr)), aptr= 0;
		for(int i= 1; i <= n; i++) edg[i].clear();
		for(int i= 1; i <= m; i++) {
			cin >> tmpx >> tmpy;
			edg[tmpy].push_back(tmpx), ++r[tmpx];
		}
		for(int i= 1; i <= n; i++)
			if(!r[i]) qu.push(i);
		while(!qu.empty()) {
			tmpx= qu.top(), qu.pop(), ans[++aptr]= tmpx;
			for(int i= 0; i < edg[tmpx].size(); i++)
				if(++yr[edg[tmpx][i]] == r[edg[tmpx][i]]) qu.push(edg[tmpx][i]);
		}
		if(aptr != n) {
			cout << "Impossible!" << endl;
			continue;
		}
		for(int i= n; i; i--) cout << ans[i] << ' ';
		cout << endl;
	}
	return 0;
}