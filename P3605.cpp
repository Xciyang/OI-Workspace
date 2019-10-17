#include <iostream>
#include <stdio.h>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;
int n, m, v[100005], a[100005], b[100005], tmpx, tmpy, f[100005];
map< int, int > mm;
vector< int > edg[100005];
inline int lowb(int x) {
	return x & -x;
}
inline int query(int x) {
	int res= 0;
	for(; x; x-= lowb(x)) res+= v[x];
	return res;
}
inline void update(int x, int c) {
	for(; x <= m; x+= lowb(x)) v[x]+= c;
	return;
}
void dfs(int nown) {
	int res= query(m) - query(mm[b[nown]]);
	for(int i= 0, to; i < (int)edg[nown].size(); i++) {
		to= edg[nown][i];
		dfs(to);
	}
	f[nown]= query(m) - query(mm[b[nown]]) - res;
	update(mm[b[nown]], 1);
	return;
}
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i], b[i]= a[i];
	for(int i= 2; i <= n; i++) cin >> tmpx, edg[tmpx].push_back(i);
	sort(a + 1, a + n + 1);
	m= unique(a + 1, a + n + 1) - a - 1;
	for(int i= 1; i <= m; i++) mm[a[i]]= i;
	dfs(1);
	for(int i= 1; i <= n; i++) cout << f[i] << endl;
	return 0;
}