#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int q, n, ans, anss[105], p[105], ok, tmp[105];
void dfs(int k, int v, int nown) {
	if(k == ans) {
		if(!v) ok= 1, memcpy(anss, tmp, sizeof(tmp));
		return;
	}
	if(nown > n || p[nown] > anss[k]) return;
	tmp[k]= p[nown];
	for(int i= 1; p[nown] * i <= v; i++) dfs(k + 1, v - i * p[nown], nown + 1);
	dfs(k, v, nown + 1);
	return;
}
int main() {
	cin >> q >> n;
	for(int i= 1; i <= n; i++) cin >> p[i];
	sort(p + 1, p + n + 1), memset(anss, 0x3f, sizeof(anss));
	for(ans= 1; ans <= n; ans++)
		if(dfs(0, q, 1), ok) break;
	cout << ans;
	for(int i= 0; i < ans; i++) cout << ' ' << anss[i];
	cout << endl;
	return 0;
}