#include <iostream>
#include <stdio.h>
#include <set>
#include <string.h>
using namespace std;
int n, m, tmpx, tmpy, tmpl, head[500005], edptr= 1;
struct EDGE {
	int to, nexty, dis;
} eds[1000005];
void add(int a, int b, int c) {
	eds[edptr].to= b, eds[edptr].nexty= head[a], eds[edptr].dis= c;
	head[a]= edptr++;
	return;
}
long long cnt, nk;
int dfs(int nown, int fa) {
	multiset< long long > mu;
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == fa) continue;
		long long res= dfs(to, nown) + eds[i].dis;
		if(res >= nk)
			++cnt;
		else
			mu.insert(res);
	}
	long long maxd= 0;
	while(!mu.empty()) {
		long long nowx= *mu.begin();
		if(mu.size() == 1) return max(nowx, maxd);
		mu.erase(mu.begin());
		multiset< long long >::iterator it= mu.lower_bound(nk - nowx);
		if(it == mu.end()) {
			maxd= max(nowx, maxd);
			continue;
		}
		++cnt, mu.erase(it);
	}
	return maxd;
}
int judge(long long k) {
	nk= k, cnt= 0, dfs(1, 0);
	return cnt >= m;
}
long long dep[500005], maxn;
void DFS(int nown, int fa) {
	if(dep[nown] > dep[maxn]) maxn= nown;
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == fa) continue;
		dep[to]= dep[nown] + eds[i].dis;
		DFS(to, nown);
	}
	return;
}
int main() {
	long long l= 0, r= 0, mid, ans;
	scanf("%d%d", &n, &m);
	for(int i= 1; i < n; i++) {
		scanf("%d%d%d", &tmpx, &tmpy, &tmpl);
		add(tmpx, tmpy, tmpl), add(tmpy, tmpx, tmpl);
	}
	maxn= 1, DFS(1, 0), memset(dep, 0, sizeof(dep)), DFS(maxn, 0);
	r= dep[maxn];
	while(l <= r) {
		mid= (l + r) >> 1;
		if(judge(mid))
			ans= mid, l= mid + 1;
		else
			r= mid - 1;
	}
	printf("%lld\n", ans);
	return 0;
}