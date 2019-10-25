#include <iostream>
#include <stdio.h>
using namespace std;
int n, m;
struct OPT {
	int x, y, z;
} opts[200005];
// 1 -> 2 -> 3 -> 1
int sl[4][4], a[200005];
int lz[200005], r[200005];
inline void work() {
	for(int i= 1; i <= n; i++) lz[i]= i, r[i]= 1;
	for(int i= 1; i <= m; i++) {
		if(opts[i].x == 1) {
			int x= lz[opts[i].y], y= lz[opts[i].z];
			lz[opts[i].z]= 0;
			if(sl[a[x]][a[y]])
				r[x]= 0, lz[opts[i].y]= y;
			else
				r[y]= 0;
		}
		else {
			opts[i].z+= r[opts[i].y];
		}
	}
	return;
}
void dfs(int nown) {
	if(nown == n + 1) {
		work();
		return;
	}
	for(int i= 1; i <= 3; i++) {
		a[nown]= i;
		dfs(nown + 1);
	}
	return;
}
int main() {
	sl[2][1]= sl[3][2]= sl[1][3]= 1;
	cin >> n >> m;
	for(int i= 1; i <= m; i++) {
		cin >> opts[i].x >> opts[i].y;
		if(opts[i].x == 1) cin >> opts[i].z;
	}
	dfs(1);
	for(int i= 1; i <= m; i++)
		if(opts[i].x == 2) cout << opts[i].z << endl;
	return 0;
}