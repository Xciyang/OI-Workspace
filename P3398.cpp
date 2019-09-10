#include <iostream>
#include <stdio.h>
using namespace std;
int n, q, head[100005], edptr= 1, tmpx, tmpy, tmpz, tmpk;
struct EDGE {
	int to, nexty;
} eds[200005];
void add(int a, int b) {
	eds[edptr].to= b, eds[edptr].nexty= head[a];
	head[a]= edptr++;
	return;
}
int dep[100005], f[100005][17];
void dfs(int nown, int fa) {
	dep[nown]= dep[fa] + 1, f[nown][0]= fa;
	for(int i= 1; i < 17; i++) f[nown][i]= f[f[nown][i - 1]][i - 1];
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == fa) continue;
		dfs(to, nown);
	}
	return;
}
inline int getlca(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i= 16; i >= 0; i--)
		if(dep[f[x][i]] >= dep[y]) x= f[x][i];
	if(x == y) return x;
	for(int i= 16; i >= 0; i--)
		if(f[x][i] != f[y][i]) x= f[x][i], y= f[y][i];
	return f[x][0];
}
int main() {
	cin >> n >> q;
	for(int i= 1; i < n; i++) {
		cin >> tmpx >> tmpy;
		add(tmpx, tmpy), add(tmpy, tmpx);
	}   
	dfs(1, 0);
	for(int i= 1, lca1, lca2; i <= q; i++) {
		cin >> tmpx >> tmpy >> tmpz >> tmpk;
		lca1= getlca(tmpx, tmpy), lca2= getlca(tmpz, tmpk);
		if(dep[lca1] == dep[lca2]) {
			cout << (lca1 == lca2 ? 'Y' : 'N') << endl;
			continue;
		}
		else if(dep[lca1] > dep[lca2]) {
			if(getlca(lca1, tmpz) == lca1 || getlca(lca1, tmpk) == lca1) {
				cout << 'Y' << endl;
				continue;
			}
			cout << 'N' << endl;
		}
		else {
			if(getlca(lca2, tmpx) == lca2 || getlca(lca2, tmpy) == lca2) {
				cout << 'Y' << endl;
				continue;
			}
			cout << 'N' << endl;
		}
	}
	return 0;
}
