#include <iostream>
#include <stdio.h>
#include <map>
#include <algorithm>
using namespace std;
int n, m, k, x, y, num[200005], w[200005], siz[200005];
long long ans;
struct NODE {
	int l, r, c;
} a[100005];
map< int, int > mm;
int f[41][4], f2[41];
void calc() {
	long long res = 0;
	for(int i = 1; i <= k * 2; i++) {
		f2[i] = 0;
		for(int j = 1; j <= 3; j++) {
			f[i][j] = 0;
		}
	}
	for(int i = 1; i <= m; i++) {
		if(w[i]) {
			for(int j = a[i].l; j <= a[i].r; j++) {
				f[j][a[i].c] = 1;
			}
		}
	}
	for(int i = 1; i <= k * 2; i++) {
		int flag = 0;
		for(int j = 1; j <= 3; j++) {
			if(f[i][j]) {
				f2[i] += f[i][j];
			}
		}
		if(f2[i] == 1) {
			res += 1ll * x * siz[i];
		}
		else if(f2[i] > 1) {
			res -= 1ll * y * siz[i];
		}
	}
	ans = max(ans, res);
	return;
}
void dfs(int nown) {
	if(nown == m + 1) {
		calc();
		return;
	}
	w[nown] = 1;
	dfs(nown + 1);
	w[nown] = 0;
	dfs(nown + 1);
	return;
}
int main() {
	cin >> n >> m >> x >> y;
	for(int i = 1; i <= m; i++) {
		cin >> a[i].c >> a[i].l >> a[i].r;
		num[++num[0]] = a[i].l;
		num[++num[0]] = a[i].r;
	}
	sort(num + 1, num + num[0] + 1);
	k = unique(num + 1, num + num[0] + 1) - num - 1;
	for(int i = 1; i <= k; i++) mm[num[i]] = i, siz[i * 2 - 1] = num[i] - num[i - 1] - 1, siz[i * 2] = 1;
	for(int i = 1; i <= m; i++) a[i].l = mm[a[i].l] * 2, a[i].r = mm[a[i].r] * 2;
	dfs(1);
	cout << ans << endl;
	return 0;
}
/*
8 2 10 5
1 5 6
3 6 8
*/