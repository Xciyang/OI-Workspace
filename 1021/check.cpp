#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
using namespace std;
#define input "./a.in"
#define out "./a.out"
int n, fa[300005], tmpx, tmpy, dep[300005], ans[300005];
vector< int > edg[300005];
char tmps[300005];
void dfs(int nown) {
	dep[nown]= dep[fa[nown]] + 1;
	for(int i= 0; i < edg[nown].size(); i++) {
		if(edg[nown][i] != fa[nown]) {
			fa[edg[nown][i]]= nown, dfs(edg[nown][i]);
		}
	}
	return;
}
int check(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	int res= 0;
	while(dep[x] > dep[y]) x= fa[x], ++res;
	while(x != y) x= fa[x], y= fa[y], res+= 2;
	return res;
}

int main() {
	ifstream finput(input);
	finput >> n;
	for(int i= 1; i < n; i++) {
		finput >> tmpx >> tmpy;
		edg[tmpx].push_back(tmpy), edg[tmpy].push_back(tmpx);
	}
	dfs(1);
	ifstream fout(out);
	fout >> tmps;
	for(int i= 1; i <= n; i++) fout >> ans[i];
	for(int i= 1; i <= n; i++) {
		if(check(ans[i], ans[i % n + 1]) > 3) {
			cout << "No!" << endl;
			cout << ans[i] << ' ' << ans[i % n + 1] << ' ' << check(ans[i], ans[i % n + 1]) << endl;
			system("pause");
			return 0;
		}
	}
	cout << "OK!" << endl;
	system("pause");
	return 0;
}