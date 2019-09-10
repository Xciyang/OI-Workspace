#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
int n, m, a[100005], chose[100005], nxt[100005], pre[100005], bptr;
priority_queue< pair< int, int > > qu;
int e[2];
int main() {
	scanf("%d", &n);
	for(int i= 1; i <= n; i++) scanf("%d", a + i), qu.push(make_pair(a[i], i)), nxt[i]= i + 1, pre[i]= i - 1;
	for(int i= 1; i < (n >> 1); i++) {
		m= qu.top().second, qu.pop();
		while(chose[m]) m= qu.top().second, qu.pop();
		if(m == n) {
			e[1]= n, --i;
			continue;
		}
		chose[m]= chose[nxt[m]]= 1;
		printf("%d %d ", a[m], a[nxt[m]]);
		nxt[pre[m]]= nxt[nxt[m]], pre[nxt[nxt[m]]]= pre[m];
	}
	m= qu.top().second, qu.pop();
	while(chose[m]) m= qu.top().second, qu.pop();
	e[0]= m;
	if(!e[1] || chose[e[1]]) {
		m= qu.top().second, qu.pop();
		while(chose[m]) m= qu.top().second, qu.pop();
		e[1]= m;
	}
	if(e[0] > e[1]) swap(e[0], e[1]);
	printf("%d %d\n", a[e[0]], a[e[1]]);
	return 0;
}