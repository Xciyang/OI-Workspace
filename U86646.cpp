#include <iostream>
#include <stdio.h>
using namespace std;
int n, f[1000005], v[1000005], ans[1000005];
int dfs(int nown, int c) {
	if(v[nown]) return v[nown] != c + 1;
	v[nown]= c + 1;
	if(dfs(f[nown], c ^ 1)) {
		v[nown]= 0;
		return 1;
	}
	return 0;
}
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> f[i];
	for(int i= 1; i <= n; i++) {
		if(dfs(i, 1)) {
			if(dfs(i, 0)) {
				cout << "No Solution" << endl;
				return 0;
			}
		}
		if(v[i] == 2) ans[++ans[0]]= i;
	}
	for(int i= 1; i <= ans[0]; i++) {
		cout << ans[i];
		if(i != ans[0]) cout << ' ';
	}
	return 0;
}