#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, k, f[205][105];
int dfs(int nn, int nk) {
	if(f[nn][nk] != -1) return f[nn][nk];
	f[nn][nk]= 0;
	if(nk > (nn + 1) / 2 || nk <= 1 || nn <= 1) return 0;
	for(int i= 1; i < nn; i+= 2)
		for(int j= 1; j < nk; j++) f[nn][nk]= (f[nn][nk] + dfs(nn - i - 1, j) * dfs(i, nk - 1) * (j != nk - 1 ? 2 : 1)) % 9901;
	return f[nn][nk];
}
int main() {
	cin >> n >> k;
	memset(f, -1, sizeof(f)), f[1][1]= 1;
	cout << dfs(n, k) << endl;
	return 0;
}