#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
char tmps[55];
int n, f[55][55], vis[55][55];
inline int judge(const char *s, const char *b, int len) {
	for(int i= 0; i < len; i++)
		if(s[i] != b[i]) return 0;
	return 1;
}
int nlen, bestans;
inline void DFS(int x, int base, int nowans) {
	if(nowans >= bestans || x < 0) return;
	if(!x) {
		bestans= nowans;
		return;
	}
	DFS(x - 1, base + 1, nowans + nlen);
	if(base) DFS(x - base, base << 1, nowans + 1);
	return;
}
void dfs2(char *b, int now, int nowans) {
	if(nowans >= bestans) return;
	if(now == nlen) {
		bestans= nowans;
		return;
	}
	if(now && now * 2 <= nlen && judge(b, b + now, now)) dfs2(b, now * 2, nowans + 1);
	dfs2(b, now + 1, nowans + 1);
	return;
}
int dfs(int l, int r) {
	if(vis[l][r]) return f[l][r];
	vis[l][r]= 1;
	if(l == r) return f[l][r]= 1;
	int res= r - l + 1, len= r - l + 1;
	for(int i= l; i < r; i++) res= min(res, dfs(l, i) + dfs(i + 1, r));
	for(int i= 1; i < len; i++) {
		if(len % i != 0) continue;
		int flag= 1;
		for(int j= l + i; j <= r; j+= i)
			if(!judge(tmps + l, tmps + j, i)) {
				flag= 0;
				break;
			}
		if(flag) {
			nlen= i, bestans= res, dfs2(tmps + l, 0, 0);
			nlen= bestans, bestans= res, DFS(len / i, 0, 0);
			res= min(res, (l != 1) + bestans);
		}
	}
	return f[l][r]= res;
}
int main() {
	cin >> (tmps + 1);
	n= strlen(tmps + 1);
	dfs(1, n);
	cout << f[1][n] << endl;
	return 0;
}