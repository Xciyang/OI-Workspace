#include <iostream>
#include <stdio.h>
#include <map>
using namespace std;
int n, p, c, a[50], f[35][10005];
int psdfs(int nown, int res) {
	if(f[nown][res]) return f[nown][res];
	return f[nown][res]= (nown == n + 1 ? 0 : (psdfs(nown + 1, (long long)res * a[nown] % p) + psdfs(nown + 1, res)) % 1000000007);
}
map< int, map< int, int > > f2;
int psdfs2(int nown, int res) {
	if(f2[nown][res]) return f2[nown][res];
	return f2[nown][res]= (nown == n + 1 ? 0 : (psdfs2(nown + 1, (long long)res * a[nown] % p) + psdfs2(nown + 1, res)) % 1000000007);
}
int main() {
	cin >> n >> p >> c;
	for(int i= 1; i <= n; i++) cin >> a[i];
	if(p <= 10000) {
		f[n + 1][c]= 1;
		cout << psdfs(1, 1) << endl;
	}
	else {
		f2[n + 1][c]= 1;
		cout << psdfs2(1, 1) << endl;
	}
	return 0;
}