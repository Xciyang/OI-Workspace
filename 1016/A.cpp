#include <iostream>
#include <stdio.h>
using namespace std;
int n, ans[100005], vis[100005], f[100005], cnt, ANS= 1;
char tmps[100005];
const int mod= 998244353;
int catalan(int x) {
	if(vis[x]) return ans[x];
	vis[x]= 1;
	if(x == 1 || x == 2) return ans[x]= 1;
	for(int i= 1; i < x; i++) ans[x]= (ans[x] + 1LL * catalan(i) * catalan(x - i)) % mod;
	return ans[x];
}
int main() {
	cin >> n >> (tmps + 1);
	cnt= 1;
	for(int i= 2; i <= n; i++) {
		if(tmps[i] != tmps[i - 1]) ANS= 1LL * ANS * catalan(cnt + 1) % mod, cnt= 0;
		++cnt;
	}
	if(cnt) ANS= 1LL * ANS * catalan(cnt + 1) % mod;
	cout << ANS << endl;
	return 0;
}
/*
10
0100100000

10
1000100000
*/