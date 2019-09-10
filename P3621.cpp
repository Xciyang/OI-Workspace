#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int n, son[100001][2], maxdep, mindep= 100001, ans, flag;
void dfs(int nown, int dep) {
	if(nown == -1) {
		maxdep= max(maxdep, dep), mindep= min(mindep, dep);
		return;
	}
	dfs(son[nown][0], dep + 1), dfs(son[nown][1], dep + 1);
	return;
}
/*
 * 左边全是小深度的，右边全是大深度的
 *
 * 左边全是小深度的，右边大小深度都有
 *
 * 左边大小深度都有，右边全是大深度的
 *
 * 深度越小越靠上
 */
int work(int nown, int dep) {
	if(nown == -1) return dep == maxdep;
	int tmpx= work(son[nown][0], dep + 1), tmpy= work(son[nown][1], dep + 1);
	if((tmpx == 0 && tmpy == 1) || (tmpx == 2 && tmpy == 1) || (tmpx == 0 && tmpy == 2)) ++ans;
	if(tmpx == 2 && tmpy == 2) {
		cout << -1 << endl;
		exit(0);
	}
	if(tmpx == 2 || tmpy == 2) return 2;
	if(tmpx != tmpy) return 2;
	return tmpx;
}
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> son[i][0] >> son[i][1];
	dfs(1, 0);
	if(maxdep - mindep > 1) {
		cout << -1 << endl;
		return 0;
	}
	if(maxdep == mindep) {
		cout << 0 << endl;
		return 0;
	}
	work(1, 0);
	cout << ans << endl;
	return 0;
}