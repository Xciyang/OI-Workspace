#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, s, w[100005], ans[100005], cs[100005];
int main() {
	cin >> n >> m >> s;
	for(int i= 1; i <= m; i++) cin >> w[i];
	w[m + 1]= n;
	for(int i= 1, nown= 0; i <= m + 1; i++)
		if(w[i] - w[nown] >= s) nown= ans[++ans[0]]= i, cs[i]= 1;
	for(int i= m, nown= m + 1; i >= 0; i--)
		if(w[nown] - w[i] >= s && !cs[i]) nown= ans[++ans[0]]= i, cs[i]= 1;
	if(ans[0] == m + 2) {
		cout << "YES" << endl;
		for(int i= 1; i <= m + 2; i++) cout << ans[i] << ' ';
		return 0;
	}
	cout << "NO" << endl;
	return 0;
}