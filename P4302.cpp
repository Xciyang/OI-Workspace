#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
char tmps[105];
int f[105][105], n, vis[105][105];
inline int num(int x) {
	int cnt= 0;
	while(x) ++cnt, x/= 10;
	return cnt;
}
inline int judge(char *b, char *s, int len) {
	for(int i= 0; i < len; i++)
		if(b[i] != s[i]) return 0;
	return 1;
}
int deal(int l, int r) {
	if(vis[l][r]) return f[l][r];
	vis[l][r]= 1;
	if(l == r) return f[l][r]= 1;
	int res= r - l + 1;
	for(int i= l; i < r; i++) res= min(res, deal(l, i) + deal(i + 1, r));
	for(int i= 1; i <= (r - l + 1) / 2; i++) {
		if((r - l + 1) % i != 0) continue;
		int flag= 1;
		for(int L= l + i; L <= r; L+= i) {
			if(!judge(tmps + l, tmps + L, i)) {
				flag= 0;
				break;
			}
		}
		if(flag) res= min(res, deal(l, l + i - 1) + 2 + num((r - l + 1) / i));
	}
	return f[l][r]= res;
}
int main() {
	cin >> (tmps + 1), n= strlen(tmps + 1);
	deal(1, n);
	cout << f[1][n] << endl;
	return 0;
}
/*
AAAAAAAAAABABABCCD
*/