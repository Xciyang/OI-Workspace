#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int n, p[200005][19], v[200005], a[200005], dep[200005], fid[200005];
vector< int > edg[200005];
long long ans;
void dfs(int nown) {
	dep[nown]= dep[p[nown][0]] + 1;
	for(int i= 1; i <= 18; i++) p[nown][i]= p[p[nown][i - 1]][i - 1];
	for(int i= 0; i < (int)edg[nown].size(); i++) dfs(edg[nown][i]);
	return;
}
int getf(int x, int y) {
	if(!x || !y) return x + y;
	if(x == y) return x;
	if(dep[x] < dep[y]) swap(x, y);
	for(int i= 18; i >= 0; i--) {
		if(dep[p[x][i]] >= dep[y]) x= p[x][i];
	}
	if(x == y) return y;
	for(int i= 18; i >= 0; i--) {
		if(p[x][i] != p[y][i]) x= p[x][i], y= p[y][i];
	}
	return p[x][0];
}
int lcv[900005];
void build(int nown, int l, int r) {
	if(l == r) {
		lcv[nown]= a[l];
		return;
	}
	int mid= (l + r) >> 1;
	build(nown << 1, l, mid), build(nown << 1 | 1, mid + 1, r);
	lcv[nown]= getf(lcv[nown << 1], lcv[nown << 1 | 1]);
	return;
}
int query(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) return lcv[nown];
	int mid= (l + r) >> 1, lres= 0, rres= 0;
	if(mid >= ml) lres= query(nown << 1, l, mid, ml, mr);
	if(mid < mr) rres= query(nown << 1 | 1, mid + 1, r, ml, mr);
	return getf(lres, rres);
}
// int s[200005];
// inline int lowb(int x) {
// 	return x & -x;
// }
// inline void change(int x, int c) {
// 	for(; x <= n; x+= lowb(x)) s[x]+= c;
// 	return;
// }
// inline int query(int x) {
// 	int res= 0;
// 	for(; x; x-= lowb(x)) res+= s[x];
// 	return res;
// }
inline int cmpfid(const int &x, const int &y) {
	return fid[x] < fid[y];
}
// void dfs2(int nown) {
// 	int suml= 0, sumr= 0;
// 	for(int i= 0, to; i < edg[nown].size(); i++) {
// 		to= edg[nown][i];
// 		int lastl= query(fid[nown]), lastr= query(n) - query(fid[nown]);
// 		dfs2(to);
// 		int detl= query(fid[nown]) - lastl, detr= query(n) - query(fid[nown]) - lastr;
// 		ans+= 1ll * detl * sumr * v[nown] + 1ll * detr * suml * v[nown];
// 		suml+= detl, sumr+= detr;
// 	}
// 	ans+= 1ll * (suml + sumr + 1) * v[nown];
// 	change(fid[nown], 1);
// 	return;
// }
int aptr= 1;
int check(int nown) {
	if(a[aptr] != nown) return 0;
	++aptr;
	for(int i= 0; i < edg[nown].size(); i++)
		if(!check(edg[nown][i])) return 0;
	return 1;
}
int siz[200005];
void dfs2(int nown) {
	siz[nown]= 1;
	ans+= v[nown];
	for(int i= 0; i < edg[nown].size(); i++) {
		dfs2(edg[nown][i]);
		ans+= 1ll * siz[nown] * siz[edg[nown][i]] * v[nown];
		siz[nown]+= siz[edg[nown][i]];
	}
	return;
}
int main() {
	freopen("sagittarius.in", "r", stdin);
	freopen("sagittarius.out", "w", stdout);
	cin >> n;
	for(int i= 2; i <= n; i++) {
		cin >> p[i][0];
		edg[p[i][0]].push_back(i);
	}
	for(int i= 1; i <= n; i++) cin >> a[i], fid[a[i]]= i;
	for(int i= 1; i <= n; i++) cin >> v[i];
	for(int i= 1; i <= n; i++) sort(edg[i].begin(), edg[i].end(), cmpfid);
	if(n > 2000 && check(1)) {
		dfs2(1);
		cout << ans << endl;
		return 0;
	}
	dfs(1);
	build(1, 1, n);
	for(int i= 1; i <= n; i++) {
		for(int j= i; j <= n; j++) {
			ans+= v[query(1, 1, n, i, j)];
		}
	}
	// dfs2(1);
	cout << ans << endl;
	return 0;
}
/*
6
1 2 2 1 1
1 2 3 4 5 6
1 2 3 4 5 6
*/