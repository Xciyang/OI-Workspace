#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
int n, X, Y, Z, tmpx, w[105], wptr, ans, cnt;
int wp[105], c[105], b[105], frac[105];
const int MOD= 998244353;
long long qpow(long long A, long long B) {
	long long ANS= 1;
	while(B) {
		if(B & 1) ANS= ANS * A % MOD;
		A= A * A % MOD, B>>= 1;
	}
	return ANS;
}
int judge() {
	int res= 0;
	for(int i= 1; i <= n; i++)
		if(b[i] - Z >= c[i]) return 1;
	return 0;
}
void dfs2(int nown) {
	if(nown == Y + 1) {
		cnt= (cnt + 1) % MOD;
		ans= (ans + judge()) % MOD;
		return;
	}
	for(int i= 1; i <= wptr; i++) {
		if(wp[i]) continue;
		wp[i]= 1, ++c[w[i]];
		dfs2(nown + 1);
		wp[i]= 0, --c[w[i]];
	}
}
void dfs(int nown) {
	if(nown == X + 1) {
		dfs2(1);
		return;
	}
	for(int i= 1; i <= wptr; i++) {
		if(wp[i]) continue;
		wp[i]= 1, ++b[w[i]];
		dfs(nown + 1);
		wp[i]= 0, --b[w[i]];
	}
	return;
}
int main() {
	frac[0]= 1;
	for(int i= 1; i <= 100; i++) frac[i]= 1LL * frac[i - 1] * i % MOD;
	cin >> n >> X >> Y >> Z;
	for(int i= 1; i <= n; i++) {
		cin >> tmpx;
		while(tmpx--) w[++wptr]= i;
	}
	dfs(1);
	cout << 1LL * ans * qpow(cnt, MOD - 2) % MOD;
	return 0;
}