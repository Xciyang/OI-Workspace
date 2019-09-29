
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
const long long N= 500000;
long long maxx[N], F[N], H[N], cnt, edptr, n, m, tmpx, tmpy, tmpz, ans= -1e9;
int lin[N * 2];
struct EDGE {
	int to, n;
	long long v;
} edg[N * 2];
struct NODE {
	long long v;
	int id;
	inline bool operator<(const NODE &q2) const {
		return v > q2.v;
	}
} a[N];
void add(long long x, long long y, long long v) {
	edg[++edptr].to= y, edg[edptr].v= v, edg[edptr].n= lin[x];
	lin[x]= edptr;
	return;
}
void dfs1(long long x, long long fa) {
	for(long long i= lin[x], to; i; i= edg[i].n) {
		to= edg[i].to;
		if(to == fa) continue;
		dfs1(to, x), F[x]= max(F[x], F[to]), F[x]= max(F[x], maxx[x] + maxx[to] + edg[i].v), maxx[x]= max(maxx[x], maxx[to] + edg[i].v);
	}
	return;
}
void dfs2(long long x, long long fa, long long dis) {
	cnt= 1, a[1].v= dis, a[1].id= -1;
	for(long long i= lin[x], to; i; i= edg[i].n) {
		to= edg[i].to;
		if(to == fa) continue;
		a[++cnt].v= maxx[to] + edg[i].v, a[cnt].id= to;
	}
	sort(a + 1, a + cnt + 1);
	for(long long i= lin[x], to; i; i= edg[i].n) {
		to= edg[i].to;
		if(to == fa) continue;
		long long sum= 0;
		for(long long j= 1, tot= 0; j <= cnt && tot < 2; j++) {
			if(a[j].id == to) continue;
			++tot, sum+= max((long long)0, a[j].v);
		}
		H[to]= max(sum, H[x]);
	}
	long long to1= a[1].id, to2= a[2].id, big1= a[1].v, big2= a[2].v, big3= a[3].v;
	for(long long i= lin[x], to; i; i= edg[i].n) {
		to= edg[i].to;
		if(to == fa) continue;
		if(to1 == to)
			dfs2(to, x, max((long long)0, to2 == to ? big3 : big2) + edg[i].v);
		else
			dfs2(to, x, max((long long)0, big1) + edg[i].v);
	}
	return;
}
void dfs3(long long x, long long fa, long long maxn) {
	cnt= 1, a[1].v= maxn, a[1].id= -1, ans= max(ans, (long long)F[x] * maxn);
	for(long long i= lin[x]; i; i= edg[i].n) {
		long long to= edg[i].to;
		if(to == fa) continue;
		a[++cnt].v= F[to], a[cnt].id= to;
	}
	sort(a + 1, a + cnt + 1);
	long long big= a[1].v, big2= a[2].v, to1= a[1].id;
	for(long long i= lin[x], to; i; i= edg[i].n) {
		to= edg[i].to;
		if(to == fa) continue;
		dfs3(to, x, to1 == to ? big2 : big);
	}
	return;
}
int main() {
	cin >> n;
	for(int i= 1; i < n; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		add(tmpx, tmpy, tmpz), add(tmpy, tmpx, tmpz);
	}
	dfs1(1, 1), dfs2(1, 1, 0), dfs3(1, 1, 0);
	for(int i= 1; i <= n; i++) ans= max(ans, F[i] * H[i]);
	for(int i= 1; i <= edptr; i++) edg[i].v= -edg[i].v;
	memset(F, 0, sizeof(F)), memset(H, 0, sizeof(H)), memset(maxx, 0, sizeof(maxx));
	dfs1(1, 1), dfs2(1, 1, 0), dfs3(1, 1, 0);
	for(int i= 1; i <= n; i++) ans= max(ans, F[i] * H[i]);
	cout << ans << endl;
	return 0;
}