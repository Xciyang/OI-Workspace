#include <bits/stdc++.h>
using namespace std;
template < class T >
T read() {
	T x= 0, w= 1;
	char c= getchar();
	for(; !isdigit(c); c= getchar())
		if(c == '-') w= -w;
	for(; isdigit(c); c= getchar()) x= x * 10 + c - '0';
	return x * w;
}
template < class T >
T read(T &x) {
	return x= read< T >();
}
#define CO const
#define IN inline
typedef long long LL;

CO int N= 200000 + 10;
int h[N];
LL sum[N];
int st[N], top, len[N];
int lc[N], rc[N];
LL step;

void dfs(int x, int hl, int hr) {
	if(lc[x]) {
		if(h[x] > hl)
			step+= x - lc[x], dfs(lc[x], hl, h[lc[x]]);
		else
			dfs(lc[x], hl, hl);
	}
	if(rc[x]) {
		if(h[x] > hr)
			step+= rc[x] - x, dfs(rc[x], h[rc[x]], hr);
		else
			dfs(rc[x], hr, hr);
	}
}
int main() {
	int n= read< int >();
	for(int i= 1; i <= n; ++i) read(h[i]), sum[i]= sum[i - 1] + h[i];
	LL sh= 0, ans= 0;
	for(int i= 1; i <= n; ++i) {
		int tlen= 1, lst= -1;
		for(; top and h[i] <= h[st[top]]; --top) {
			sh-= (LL)h[st[top]] * len[top];
			tlen+= len[top];
			lst= st[top];
		}
		sh+= (LL)(tlen - 1) * h[i];
		ans+= (LL)i * (i - 1) / 2;
		ans+= (LL)(i - 1) * h[i] + sum[i - 1] - 2 * sh;
		if(lst != -1) lc[i]= lst;
		if(top) rc[st[top]]= i;
		sh+= h[i];
		st[++top]= i;
		len[top]= tlen;
	}
	printf("%lld\n", ans);
	return 0;
}