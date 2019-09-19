#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
#define int long long
int n, tmpx, tmpy;
long long ans, f[100005];
vector< int > edg[100005];
inline long long qmul(long long a, long long b, long long p) {
	long long res= 0;
	while(b) {
		if(b & 1) res= (res + a) % p;
		a= (a + a) % p, b>>= 1;
	}
	return res;
}
void dfs(int nown, int fa) {
	f[nown]= 1;
	for(int i= 0, to; i < (int)edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa) continue;
		dfs(to, nown);
		f[nown]= qmul(f[nown], f[to] + 1, 1000000007);
	}
	ans= (ans + f[nown]) % 1000000007;
	return;
}
signed main() {
	cin >> n;
	for(int i= 1; i < n; i++) {
		cin >> tmpx >> tmpy;
		edg[tmpx].push_back(tmpy), edg[tmpy].push_back(tmpx);
	}
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}

// 抽象
// nown 