#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, m, t[505], ans[505][505];
int dfs(int nowc, int lastt) {
	if(nowc == n + 1) return 0;
	if(lastt < t[nowc]) return dfs(nowc, t[nowc]);
	if(ans[nowc][lastt - t[nowc]]) return ans[nowc][lastt - t[nowc]];
	int lastc= nowc, lasttt= lastt, sum= 0;
	while(lastt >= t[nowc] && nowc <= n) sum+= t[nowc++];
	int besta= (nowc - lastc) * lastt - sum + dfs(nowc, lastt + m);
	for(; nowc <= n; nowc++) {
		sum+= t[nowc];
		besta= min(besta, (nowc - lastc + 1) * t[nowc] - sum + dfs(nowc + 1, t[nowc] + m));
	}
	return ans[lastc][lasttt - t[lastc]]= besta;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i= 1; i <= n; i++) scanf("%d", t + i);
	sort(t + 1, t + n + 1);
	printf("%d\n", dfs(1, 0));
	return 0;
}