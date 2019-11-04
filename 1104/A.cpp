#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
using namespace std;
int n, p[100005], dep[100005], flag[100005];
int st[100005], past[100005];
vector< int > edg[100005];
int getdis(int x) {
	for(int i= 1; i <= n; i++) past[i]= 0;
	queue< int > qu;
	qu.push(x), past[x]= 1;
	while(!qu.empty()) {
		x= qu.front(), qu.pop();
		if(!flag[x] && !st[x]) return x;
		if(p[x] && !past[p[x]]) qu.push(p[x]), past[p[x]]= 1;
		for(int i= 0; i < edg[x].size(); i++)
			if(!past[edg[x][i]]) qu.push(edg[x][i]), past[edg[x][i]]= 1;
	}
	return 0;
}
void dfs(int nown) {
	if(!flag[nown]) {
		cout << 'Y' << endl;
		exit(0);
	}
	int res= getdis(nown);
	if(!res) return;
	st[res]= 1;
	if(p[nown]) dfs(p[nown]);
	for(int i= 0; i < edg[nown].size(); i++)
		if(!st[edg[nown][i]]) dfs(edg[nown][i]);
	st[res]= 0;
	return;
}
int main() {
	cin >> n;
	for(int i= 2; i <= n; i++) cin >> p[i], dep[i]= dep[p[i]] + 1, flag[p[i]]= 1, edg[p[i]].push_back(i);
	dfs(1);
	cout << 'D' << endl;
	return 0;
}