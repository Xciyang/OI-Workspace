#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int n, m, s, bt[10], t[10], ans;
const int mod= 998244353;
struct NODE {
	int l, r, b;
	inline int operator<(const NODE &n2) const {
		return r < n2.r;
	}
} a[200005];
void dfs(int nown) {
	if(nown == n + 1) {
		memset(bt, 0, sizeof(bt));
		for(int i= 1; i <= n; i++) 
			for(int j= 1; j <= m; j++)
				if(a[j].l <= i && i <= a[j].r && a[j].b != t[i]) bt[j]= 1;
		for(int i= 1; i <= m; i++)
			if(!bt[i]) return;
		if(++ans == mod) ans= 0;
		return;
	}
	for(int i= 1; i <= s; i++) t[nown]= i, dfs(nown + 1);
	return;
}
int main() {
	cin >> n >> m >> s;
	for(int i= 1; i <= m; i++) cin >> a[i].l >> a[i].r >> a[i].b;
	dfs(1);
	cout << ans << endl;
	return 0;
}