#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, m, need, wptr, bptr, tmpx, tmpy, tmpz, tmpk;
struct EDGE {
	int dis, x, y;
	inline int operator<(const EDGE &e2) const {
		return dis < e2.dis;
	}
} w[50005], b[50005];
int fa[50005];
inline int getf(int x) {
	return fa[x] == x ? x : (fa[x]= getf(fa[x]));
}
inline int tryf(int x, int y) {
	if(getf(x) == getf(y)) return 0;
	fa[getf(x)]= getf(y);
	return 1;
}
int main() {
	cin >> n >> m >> need;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz >> tmpk;
		++tmpx, ++tmpy;
		if(tmpk) {
			b[++bptr]= EDGE{tmpz, tmpx, tmpy};
		}
		else {
			w[++wptr]= EDGE{tmpz, tmpx, tmpy};
		}
	}
	sort(b + 1, b + bptr + 1), sort(w + 1, w + wptr + 1);
	int l= -100, r= 100, mid, ans;
	while(l <= r) {
		mid= (l + r) >> 1;
		for(int i= 1; i <= n; i++) fa[i]= i;
		int i= 1, j= 1, cnt= 0;
		while(i <= bptr && j <= wptr)
			if(b[i].dis + mid < w[j].dis)
				++i, cnt+= tryf(b[i].x, b[i].y);
			else
				++j, cnt+= tryf(w[i].x, w[i].y);
		while(i <= bptr) ++i, cnt+= tryf(b[i].x, b[i].y);
		if(i < need)
			r= mid - 1, ans= mid;
		else
			l= mid + 1;
	}
	for(int i= 1; i <= n; i++) fa[i]= i;
	int ans= 0;

	return 0;
}