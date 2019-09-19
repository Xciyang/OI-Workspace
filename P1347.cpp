#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
using namespace std;
int n, m, r[30], yr[30];
char tmps[5];
struct EDGE {
	int to, id;
};
vector< EDGE > edg[30];
inline int too(char c) {
	return c - 'A' + 1;
}
int wp[30], ins[30];
int dfs(int nown, int x) {
	wp[nown]= ins[nown]= 1;
	for(int i= 0; i < edg[nown].size(); i++) {
		if(edg[nown][i].id > x) break;
		if(ins[edg[nown][i].to]) return 1;
		if(!wp[edg[nown][i].to] && dfs(edg[nown][i].to, x)) return 1;
	}
	ins[nown]= 0;
	return 0;
}
int judgeH(int x) {
	memset(wp, 0, sizeof(wp)), memset(ins, 0, sizeof(ins));
	for(int i= 1; i <= n; i++)
		if(!wp[i] && dfs(i, x)) return 1;
	return 0;
}
int Qans[30], bestans[30];
int judgeQ(int x) {
	for(int i= 1; i <= n; i++) r[i]= yr[i]= 0;
	for(int i= 1; i <= n; i++) {
		for(int j= 0; j < edg[i].size(); j++) {
			if(edg[i][j].id > x) break;
			++r[edg[i][j].to];
		}
	}
	register int nown, to= 0, cnt= 0;
	for(int i= 1; i <= n; i++) {
		if(r[i] == 0) {
			if(to) return 0;
			to= i;
		}
	}
	while(to) {
		Qans[++cnt]= nown= to, to= 0;
		for(int i= 0; i < edg[nown].size(); i++) {
			if(edg[nown][i].id > x) break;
			if(++yr[edg[nown][i].to] == r[edg[nown][i].to]) {
				if(to) return 0;
				to= edg[nown][i].to;
			}
		}
	}
	return cnt == n;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i= 1; i <= m; i++) {
		scanf("%s", tmps);
		edg[too(tmps[0])].push_back(EDGE{too(tmps[2]), i}), ++r[too(tmps[2])];
	}
	if(judgeH(m)) {
		int l= 1, r= m, mid, ans= m;
		while(l <= r) {
			mid= (l + r) >> 1;
			if(judgeH(mid))
				ans= mid, r= mid - 1;
			else
				l= mid + 1;
		}
		int ll= 1, rr= ans - 1, ans2= -1;
		while(ll <= rr) {
			mid= (ll + rr) >> 1;
			if(judgeQ(mid))
				ans2= mid, rr= mid - 1, memcpy(bestans, Qans, sizeof(bestans));
			else
				ll= mid + 1;
		}
		if(ans2 == -1)
			printf("Inconsistency found after %d relations.\n", ans);
		else {
			printf("Sorted sequence determined after %d relations: ", ans2);
			for(int i= 1; i <= n; i++) putchar(bestans[i] + 'A' - 1);
			printf(".\n");
		}
	}
	else if(judgeQ(m)) {
		int ll= 1, rr= m, mid, ans2;
		while(ll <= rr) {
			mid= (ll + rr) >> 1;
			if(judgeQ(mid))
				ans2= mid, rr= mid - 1, memcpy(bestans, Qans, sizeof(bestans));
			else
				ll= mid + 1;
		}
		printf("Sorted sequence determined after %d relations: ", ans2);
		for(int i= 1; i <= n; i++) putchar(bestans[i] + 'A' - 1);
		printf(".\n");
	}
	else {
		printf("Sorted sequence cannot be determined.\n");
	}
	return 0;
}