#include <iostream>
#include <stdio.h>
using namespace std;
int n, l[100005], r[100005];
int a[100005], b[100005];
void dfs(int nown) {
	if(!nown) return;
	a[++a[0]]= nown;
	dfs(l[nown]), dfs(r[nown]);
	b[++b[0]]= nown;
	return;
}
int c[100005], bestans;
void dfs2(int nown) {
	if(nown == n + 1) {
		int res= 0;
		for(int i= 0; i < n; i++) {
			res+= (c[a[n - i]] << i) - (c[b[n - i]] << i);
		}
		bestans= max(bestans, res);
		return;
	}
	c[nown]= 1;
	dfs2(nown + 1);
	c[nown]= 0;
	dfs2(nown + 1);
	return;
}
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) {
		cin >> l[i] >> r[i];
	}
	dfs(1);
	dfs2(1);
	cout << bestans << endl;
	return 0;
}