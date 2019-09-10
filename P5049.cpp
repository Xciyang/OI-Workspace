#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
#include <algorithm>
#include <stack>
using namespace std;
vector< int > edg[500005];
int n, m, tmpx, tmpy, huan[500005], walkpast[500005], flag;
void dfs1(int nown, int fa) {
	walkpast[nown]= 1;
	for(int i= 0, to; i < (int)edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa) continue;
		if(walkpast[to]) {
			flag= huan[nown]= huan[to]= 1;
			return;
		}
		dfs1(to, nown);
		if(huan[nown]) {
			flag= 0;
			return;
		}
		if(huan[to] && flag) {
			huan[nown]= 1;
			return;
		}
	}
	return;
}
int ans[500005], cnt;
void dfs2(int nown, int fa) {
	ans[++cnt]= nown;
	for(int i= 0, to; i < (int)edg[nown].size(); i++) {
		to= edg[nown][i];
		if(to == fa) continue;
		dfs2(to, nown);
	}
	return;
}
int fa[500005];
void dfs3(int nown, int fh) {
	if(walkpast[nown]) return;
	ans[++cnt]= nown, walkpast[nown]= 1;
	priority_queue< int, vector< int >, greater< int > > qu;
	for(int i= 0, to; i < (int)edg[nown].size(); i++) {
		to= edg[nown][i];
		if(walkpast[to]) continue;
		qu.push(to);
	}
	register int to;
	while(!qu.empty()) {
		to= qu.top(), qu.pop();
		if(!flag && huan[to] && to > fh && qu.empty()) {
			flag= 1;
			return;
		}
		int nfh= 0x3f3f3f3f;
		if(!qu.empty() && huan[nown]) nfh= qu.top();
		dfs3(to, nfh == 0x3f3f3f3f ? fh : nfh);
	}
	return;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i= 1; i <= m; i++) scanf("%d%d", &tmpx, &tmpy), edg[tmpx].push_back(tmpy), edg[tmpy].push_back(tmpx);
	if(n == m) {
		dfs1(1, 0);
		memset(walkpast, 0, sizeof(walkpast)), flag= 0;
		dfs3(1, 0x3f3f3f3f);
	}
	else {
		for(int i= 1; i <= n; i++)
			if(!edg[i].empty()) sort(edg[i].begin(), edg[i].end());
		dfs2(1, 0);
	}
	for(int i= 1; i <= cnt; i++) printf("%d ", ans[i]);
	return 0;
}