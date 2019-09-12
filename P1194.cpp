#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
#define int long long
int A, B, val[1005][1005], vis[1005], ans;
priority_queue< pair< int, int > > qu;
void prim() {
	vis[1]= 1;
	for(int i= 2; i <= B; i++) qu.push(make_pair(-val[1][i], i));
	register int nown;
	for(int k= 1; k < B; k++) {
		while(!qu.empty() && vis[qu.top().second]) qu.pop();
		if(qu.empty()) return;
		ans+= -qu.top().first, nown= qu.top().second, qu.pop(), vis[nown]= 1;
		for(int i= 1; i <= B; i++) {
			if(vis[i]) continue;
			qu.push(make_pair(-val[nown][i], i));
		}
	}
	return;
}
signed main() {
	cin >> A >> B;
	for(int i= 1; i <= B; i++)
		for(int j= 1; j <= B; j++) cin >> val[i][j], val[i][j]= (val[i][j] ? min(A, val[i][j]) : A);
	prim();
	cout << ans + A << endl;
	return 0;
}