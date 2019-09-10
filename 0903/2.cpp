#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int t, lens;
char tmps[500], ans[500], bestans[500];
int dfs3(int x, int y, int dy) {
	if(x > lens) return 1;
	if(x == lens || tmps[x + 1] == ',') {
		if(dy) {
			ans[x]= (tmps[x] != '?') ? tmps[x] : '0';
			return 1;
		}
		ans[x]= tmps[x];
		if(tmps[x] != '?') return ans[x] > ans[y];
		ans[x]= ans[y] + 1;
		return ans[x] <= '9';
	}
	if(dy) {
		ans[x]= (tmps[x] != '?') ? tmps[x] : '0';
		return dfs3(x + 1, y + 1, 1);
	}
	if(tmps[x] == '?') {
		ans[x]= ans[y];
		if(dfs3(x + 1, y + 1, 0)) return 1;
		ans[x]= ans[y] + 1;
		if(ans[x] <= '9') return dfs3(x + 1, y + 1, 1);
	}
	else {
		if(tmps[x - 1] == ',' && tmps[x] == '0') return 0;
		ans[x]= tmps[x];
		if(ans[x] < ans[y]) return 0;
		if(ans[x] > ans[y]) return dfs3(x + 1, y + 1, 1);
		return dfs3(x + 1, y + 1, 0);
	}
	return 0;
}
int dfs(int nown, int lastl) {
	if(nown > lens) return 1;
	int cnt= nown;
	while(cnt <= lens && tmps[cnt] != ',') ++cnt;
	if(cnt - nown > nown - lastl - 1) {
		for(int i= nown, qd= 1; i < cnt; i++) {
			ans[i]= (tmps[i] == '?') ? (qd ? '1' : '0') : tmps[i];
			if(qd) {
				if(ans[i] == '0') return 0;
				qd= 0;
			}
		}
	}
	else if(cnt - nown == nown - lastl - 1)
		if(!dfs3(nown, lastl, 0)) return 0;
	ans[cnt]= ',';
	return dfs(cnt + 1, nown);
}
void dfsdh(int nown, int lasti, int llasti) {
	if(nown > lens) {
		if(lasti == nown - 1 || nown - lasti < lasti - llasti) return;
		if(dfs(1, 0)) {
			for(int i= 1; i <= lens; i++) {
				if(ans[i] == bestans[i]) continue;
				if(ans[i] > bestans[i])
					return;
				else
					break;
			}
			memcpy(bestans, ans, sizeof(bestans));
		}
		return;
	}
	if(tmps[nown] == ',') {
		if(lasti != nown - 1 && nown - lasti >= lasti - llasti) dfsdh(nown + 1, nown, lasti);
		return;
	}
	if(tmps[nown] == '?') {
		if(lasti != nown - 1 && nown - lasti >= lasti - llasti) {
			tmps[nown]= ',';
			dfsdh(nown + 1, nown, lasti);
			tmps[nown]= '?';
		}
	}
	dfsdh(nown + 1, lasti, llasti);
	return;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		memset(tmps, 0, sizeof(tmps)), memset(ans, 0, sizeof(ans)), bestans[1]= 126;
		scanf("%s", tmps + 1), lens= (int)strlen(tmps + 1);
		dfsdh(1, 0, 0);
		if(bestans[1] == 126) {
			printf("impossible\n");
			continue;
		}
		for(int i= 1; i <= lens; i++) putchar(bestans[i]);
		putchar('\n');
	}
	return 0;
}