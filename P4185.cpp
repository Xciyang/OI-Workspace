#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, m, a[100005], f[100005], siz[100005];
int getf(int x) {
	return x == f[x] ? x : f[x]= getf(f[x]);
}
struct NODE {
	int x, y, z, k;
	inline int operator<(const NODE &n2) const {
		return z > n2.z;
	}
} edg[100005], ans[100005];
inline int less_y(const NODE &n1, const NODE &n2) {
	return n1.y < n2.y;
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) {
		f[i]= i, siz[i]= 1;
	}
	for(int i= 1; i < n; i++) {
		cin >> edg[i].x >> edg[i].y >> edg[i].z;
	}
	for(int i= 1; i <= m; i++) {
		cin >> ans[i].z >> ans[i].x, ans[i].y= i;
	}
	sort(edg + 1, edg + n);
	sort(ans + 1, ans + m + 1);
	for(int i= 1, j= 1; i <= m; i++) {
		while(j < n && edg[j].z >= ans[i].z) {
		    	int x= getf(edg[j].x), y= getf(edg[j].y);
			if(x == y) continue;
			siz[y]+= siz[x], f[x]= y, ++j;
		}
		ans[i].k= siz[getf(ans[i].x)] - 1;
	}
	sort(ans + 1, ans + m + 1, less_y);
	for(int i= 1; i <= m; i++) cout << ans[i].k << endl;
	return 0;
}