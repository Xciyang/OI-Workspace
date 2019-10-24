#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m, limitn, ans;
char tmps[4005], tmps2[4005];
char df[4005];
int check(int k) {
	int i, j;
	for(i= 1, j= 0; i <= n; i++) {
		if(tmps[i] == df[j]) ++j;
		if(j == k) return 0;
	}
	for(i= 1, j= 0; i <= m; i++) {
		if(tmps2[i] == df[j]) ++j;
		if(j == k) return 0;
	}
	return 1;
}
int trydfs(int nown) {
	if(nown > ans) return 0;
	df[nown]= '\0';
	if(nown && check(nown)) return 1;
	df[nown]= '0';
	if(trydfs(nown + 1)) return 1;
	df[nown]= '1';
	if(trydfs(nown + 1)) return 1;
	return 0;
}
int main() {
	cin >> n >> m;
	limitn= min(n, m) + 1;
	cin >> (tmps + 1) >> (tmps2 + 1);
	for(ans= 1; ans <= limitn; ans++) {
		if(trydfs(0)) break;
	}
	cout << df << endl;
	return 0;
}