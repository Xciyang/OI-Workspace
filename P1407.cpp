#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <stack>
using namespace std;
int n, m, ptr, mptr;
string tmps, tmps2;
map< string, int > mm;
vector< int > edg[8005];
int dfn[8005], low[8005], dptr, wp[8005], r[8005], rptr;
stack< int > st;
void tarjan(int nown) {
	dfn[nown]= ++dptr, low[nown]= dfn[nown], wp[nown]= 1;
	st.push(nown);
	register int to;
	for(int i= 0; i < edg[nown].size(); i++) {
		to= edg[nown][i];
		if(!dfn[to])
			tarjan(to), low[nown]= min(low[nown], low[to]);
		else if(wp[to])
			low[nown]= min(low[nown], dfn[to]);
	}
	if(dfn[nown] == low[nown]) {
		++rptr;
		while(st.top() != nown) r[st.top()]= rptr, wp[st.top()]= 0, st.pop();
		r[st.top()]= rptr, wp[st.top()]= 0, st.pop();
	}
	return;
}
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) {
		cin >> tmps >> tmps2;
		mm[tmps]= ++mptr, mm[tmps2]= ++mptr;
		edg[mm[tmps2]].push_back(mm[tmps]);
	}
	cin >> m;
	for(int i= 1; i <= m; i++) {
		cin >> tmps >> tmps2;
		edg[mm[tmps]].push_back(mm[tmps2]);
	}
	for(int i= 1; i <= mptr; i++)
		if(!dfn[i]) tarjan(i);
	for(int i= 1; i <= mptr; i+= 2) {
		if(r[i] != r[i + 1])
			printf("Safe\n");
		else
			printf("Unsafe\n");
	}
	return 0;
}