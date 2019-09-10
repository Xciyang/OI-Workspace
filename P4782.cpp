#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;
inline int read() {
	int e= 0, f= 1;
	char ch= getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') e= e * 10 + ch - '0', ch= getchar();
	return e * f;
}
int n, m, tmpx, tmpy, tmpz, tmpk;
vector< int > edge[2000006];
stack< int > st;
int c[2000006], cptr, dfn[2000006], low[2000006], dfnptr;
int walkpast[2000006];
void tarjan(int nown) {
	low[nown]= dfn[nown]= ++dfnptr;
	walkpast[nown]= 1, st.push(nown);
	register int to;
	for(int i= 0; i < (int)edge[nown].size(); i++) {
		to= edge[nown][i];
		if(!dfn[to])
			tarjan(to), low[nown]= min(low[nown], low[to]);
		else if(walkpast[to])
			low[nown]= min(low[nown], dfn[to]);
	}
	if(dfn[nown] == low[nown]) {
		++cptr;
		while(true) {
			to= st.top(), st.pop();
			c[to]= cptr, walkpast[to]= 0;
			if(to == nown) break;
		}
	}
	return;
}
int main() {
	n= read(), m= read();
	for(int i= 1; i <= m; i++) {
		tmpx= read(), tmpy= read(), tmpz= read(), tmpk= read();
		edge[tmpx + n * tmpy].push_back(tmpz + n * (tmpk ^ 1));
		edge[tmpz + n * tmpk].push_back(tmpx + n * (tmpy ^ 1));
	}
	for(int i= 1; i <= n + n; i++)
		if(!dfn[i]) tarjan(i);
	for(int i= 1; i <= n; i++) {
		if(c[i] == c[i + n]) {
			printf("IMPOSSIBLE\n");
			return 0;
		}
	}
	printf("POSSIBLE\n");
	for(int i= 1; i <= n; i++) putchar((c[i] < c[i + n]) + '0'), putchar(' ');
	putchar('\n');
	return 0;
}