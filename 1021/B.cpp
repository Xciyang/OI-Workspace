#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <time.h>
using namespace std;
int n, m, ans, cost[200005], xz[200005], len;
char words[200005], tmps[200005];
struct QJ {
	int l, r;
};
vector< QJ > qjs;
int v[200005];
inline int lowb(int x) {
	return x & -x;
}
inline void update(int x, int c) {
	for(; x <= n; x+= lowb(x)) v[x]+= c;
	return;
}
inline int query(int x) {
	int res= 0;
	for(; x; x-= lowb(x)) res+= v[x];
	return res;
}
inline int judge() {
	for(int i= 0; i < qjs.size(); i++)
		if(query(qjs[i].r) - query(qjs[i].l - 1) == 0) return 0;
	return 1;
}
void SA() {
	int nowans= 0;
	memset(v, 0, sizeof(v));
	for(int i= 1; i <= n; i++) xz[i]= 1, nowans+= cost[i], update(i, 1);
	for(int i= 1; i <= n; i++) {
		if(!nowans) return;
		int x= rand() % n + 1;
		while(!xz[x]) x= rand() % n + 1;
		nowans-= cost[x], xz[x]= 0, update(x, -1);
		int flag= judge();
		if(flag) {
			if(nowans <= ans) ans= nowans;
		}
		else
			nowans+= cost[x], xz[x]= 1, update(x, 1), i+= rand() % 2;
	}
	return;
}
void dfs(int nown, int cst) {
	if(nown == qjs.size()) {
		ans= min(ans, cst);
		return;
	}
	if(query(qjs[nown].r) - query(qjs[nown].l - 1) != 0) {
		dfs(nown + 1, cst);
		return;
	}
	for(int i= qjs[nown].l; i <= qjs[nown].r; i++) {
		update(i, 1);
		dfs(nown + 1, cst + cost[i]);
		update(i, -1);
	}
	return;
}
int main() {
	srand(time(0));
	cin >> n >> m;
	cin >> (words + 1);
	for(int i= 1; i <= n; i++) cin >> cost[i], ans+= cost[i];
	for(int i= 1; i <= m; i++) {
		cin >> (tmps + 1), len= strlen(tmps + 1);
		char *s= strstr(words + 1, tmps + 1);
		while(s) {
			qjs.push_back(QJ{s - words, s - words + len - 1});
			s= strstr(s + 1, tmps + 1);
		}
	}
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}
/*
5 3
abcde
3 1 3 1 3
abc
bcd
cde
*/