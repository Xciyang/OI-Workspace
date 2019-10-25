#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, q;
inline int beyond(int x, int y) {
	return x < 1 || x > n || y < 1 || y > m;
}
inline int calc(int x, int y) {
	return (x - 1) * m + y;
}
char dx[1000006];
int siz[1000006], fa[1000006], tmpx, tmpy, tmpz, tmpk, tans, nowans;
inline int getf(int x) {
	if(fa[x] == x) return x;
	return fa[x]= getf(fa[x]);
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) {
			cin >> dx[calc(i, j)];
			fa[calc(i, j)]= calc(i, j);
			if(dx[calc(i, j)] == '.') {
				siz[calc(i, j)]= 1;
				if(!beyond(i - 1, j) && dx[calc(i - 1, j)] == '.') {
					int fx= getf(calc(i, j)), fy= getf(calc(i - 1, j));
					if(fx != fy) fa[fx]= fy, siz[fy]+= siz[fx];
				}
				if(!beyond(i, j - 1) && dx[calc(i, j - 1)] == '.') {
					int fx= getf(calc(i, j)), fy= getf(calc(i, j - 1));
					if(fx != fy) fa[fx]= fy, siz[fy]+= siz[fx];
				}
			}
		}
	}
	cin >> q;
	while(q--) {
		cin >> tmpx >> tmpy;
		if(tmpx == 1) {
			nowans= tans= -1;
			for(int i= 1; i <= tmpy; i++) {
				cin >> tmpz >> tmpk;
				if(siz[getf(calc(tmpz, tmpk))] > tans) {
					tans= siz[getf(calc(tmpz, tmpk))];
					nowans= i;
				}
			}
			cout << nowans << endl;
		}
		else {
			for(int i= 1; i <= tmpy; i++) {
				cin >> tmpz >> tmpk;
				if(dx[calc(tmpz, tmpk)] == '*') {
					dx[calc(tmpz, tmpk)] == '.', ++siz[calc(tmpz, tmpk)];
					int fx, fy;
					if(!beyond(tmpz - 1, tmpk) && dx[calc(tmpz - 1, tmpk)] == '.') {
						fx= getf(calc(tmpz, tmpk)), fy= getf(calc(tmpz - 1, tmpk));
						if(fx != fy) fa[fx]= fy, siz[fy]+= siz[fx];
					}
					if(!beyond(tmpz, tmpk - 1) && dx[calc(tmpz, tmpk - 1)] == '.') {
						fx= getf(calc(tmpz, tmpk)), fy= getf(calc(tmpz, tmpk - 1));
						if(fx != fy) fa[fx]= fy, siz[fy]+= siz[fx];
					}
					if(!beyond(tmpz + 1, tmpk) && dx[calc(tmpz + 1, tmpk)] == '.') {
						fx= getf(calc(tmpz, tmpk)), fy= getf(calc(tmpz + 1, tmpk));
						if(fx != fy) fa[fx]= fy, siz[fy]+= siz[fx];
					}
					if(!beyond(tmpz, tmpk + 1) && dx[calc(tmpz, tmpk + 1)] == '.') {
						fx= getf(calc(tmpz, tmpk)), fy= getf(calc(tmpz, tmpk + 1));
						if(fx != fy) fa[fx]= fy, siz[fy]+= siz[fx];
					}
				}
				else {
					--siz[getf(calc(tmpz, tmpk))];
					dx[calc(tmpz, tmpk)] == '*', fa[calc(tmpz, tmpk)]= calc(tmpz, tmpk);
					if(getf(calc(tmpz, tmpk)) != calc(tmpz, tmpk)) fa[calc(tmpz, tmpk)]= calc(tmpz, tmpk);
				}
			}
		}
	}
	return 0;
}