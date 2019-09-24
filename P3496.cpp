#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
int n, m, tmpx, tmpy;
vector< int > edg[200005];
int b[200005];
queue< int > qu;
char ans[]= "KS";
int main() {
	cin >> n >> m;
	for(int i= 1; i <= m; i++) cin >> tmpx >> tmpy, edg[tmpx].push_back(tmpy), edg[tmpy].push_back(tmpx);
	for(int i= 1; i <= n; i++) b[i]= -1;
	for(int i= 1, j; i <= n; i++) {
		if(b[i] != -1) continue;
		if(edg[i].size() == 0) {
			cout << "NIE" << endl;
			return 0;
		}
		qu.push(i), b[i]= 0;
		while(!qu.empty()) {
			j= qu.front(), qu.pop();
			for(int k= 0; k < edg[j].size(); k++) {
				if(b[edg[j][k]] != -1) continue;
				b[edg[j][k]]= b[j] ^ 1, qu.push(edg[j][k]);
			}
		}
	}
	cout << "TAK" << endl;
	for(int i= 1; i <= n; i++) cout << ans[b[i]] << endl;
	return 0;
}