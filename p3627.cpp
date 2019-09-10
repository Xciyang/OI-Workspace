#include <iostream>
#include <stdio.h>
#include <stack>
#include <string.h>
#include <queue>
using namespace std;
int n, m, tmpx, tmpy, head[500001], edptr= 1, money[500001], head2[500001], edptr2= 1, ans;
int beginx, p;
struct edge {
	int to, nexty, dis;
} eds[500001], eds2[500001];
void add(int a, int b) {
	eds[edptr].to= b, eds[edptr].nexty= head[a];
	head[a]= edptr++;
	return;
}
void add2(int a, int b, int c) {
	eds2[edptr2].to= b, eds2[edptr2].dis= c, eds2[edptr2].nexty= head2[a];
	head2[a]= edptr2++;
	return;
}
int dfn[500001], low[500001], dptr, c[500001], cptr, sum[500001];
int walkpast[500001];
stack< int > st;
void tarjan(int nown) {
	dfn[nown]= low[nown]= ++dptr;
	st.push(nown);
	walkpast[nown]= 1;
	register int to;
	for(int i= head[nown]; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(!dfn[to])
			tarjan(to), low[nown]= min(low[nown], low[to]);
		else if(walkpast[to])
			low[nown]= min(low[nown], dfn[to]);
	}
	if(dfn[nown] == low[nown]) {
		++cptr;
		while(!st.empty()) {
			to= st.top(), st.pop();
			c[to]= cptr, walkpast[to]= 0;
			sum[cptr]+= money[to];
			if(nown == to) break;
		}
	}
	return;
}
int dis[500001];
queue< int > qu;
void spfa(int rc) {
	memset(dis, ~0x3f, sizeof(dis));
	memset(walkpast, 0, sizeof(walkpast));
	dis[rc]= sum[rc], walkpast[rc]= 1;
	qu.push(rc);
	register int nown, to;
	while(!qu.empty()) {
		nown= qu.front(), qu.pop();
		walkpast[nown]= 0;
		for(int i= head2[nown]; i; i= eds2[i].nexty) {
			to= eds2[i].to;
			if(dis[to] < dis[nown] + eds2[i].dis) {
				dis[to]= dis[nown] + eds2[i].dis;
				if(!walkpast[to]) {
					qu.push(to);
					walkpast[to]= 1;
				}
			}
		}
	}
	return;
}
int main() {
	cin >> n >> m;
	for(int i= 0; i < m; i++) {
		cin >> tmpx >> tmpy;
		add(tmpx, tmpy);
	}
	for(int i= 1; i <= n; i++) cin >> money[i];
	for(int i= 1; i <= n; i++)
		if(!dfn[i]) tarjan(i);
	for(int nown= 1, to; nown <= n; nown++) {
		for(int i= head[nown]; i; i= eds[i].nexty) {
			to= eds[i].to;
			if(c[nown] != c[to]) add2(c[nown], c[to], sum[c[to]]);
		}
	}
	cin >> beginx;
	spfa(c[beginx]);
	cin >> p;
	for(int i= 0; i < p; i++) {
		cin >> tmpx;
		ans= max(ans, dis[c[tmpx]]);
	}
	cout << ans << endl;
	return 0;
}