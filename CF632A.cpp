#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define int long long
int n, p, k[50], m;
char st[10];
int dfs(int nown) {
	if(nown == n + 1) return 0;
	return (dfs(nown + 1) + k[nown]) * 2;
}
signed main() {
	cin >> n >> p;
	for(int i= 1; i <= n; i++) cin >> st, k[i]= (st[4] == 'p'), m+= k[i];
	cout << (dfs(1) - m) * p / 2<< endl;
	return 0;
}