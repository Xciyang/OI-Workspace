#include <iostream>
#include <stdio.h>
using namespace std;
inline int read() {
	register int x= 0, f= 1;
	register char ch= getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') x= (x << 3) + (x << 1) + ch - '0', ch= getchar();
	return x * f;
}
int n, m, a[50001];
struct NODE {
	int sum, lans, rans, ans;
} node[200001];
void pushu(int nown) {
	node[nown].sum= node[nown << 1].sum + node[nown << 1 | 1].sum;
	node[nown].lans= max(node[nown << 1].lans, node[nown << 1].sum + node[nown << 1 | 1].lans);
	node[nown].rans= max(node[nown << 1 | 1].rans, node[nown << 1].rans + node[nown << 1 | 1].sum);
	node[nown].ans= max(max(node[nown << 1].ans, node[nown << 1 | 1].ans), node[nown << 1].rans + node[nown << 1 | 1].lans);
	return;
}
void build(int nown, int l, int r) {
	if(l == r) {
		node[nown].ans= node[nown].lans= node[nown].rans= node[nown].sum= a[l];
		return;
	}
	int mid= (l + r) >> 1;
	build(nown << 1, l, mid), build(nown << 1 | 1, mid + 1, r);
	pushu(nown);
	return;
}
NODE query(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) return node[nown];
	int mid= (l + r) >> 1;
	if(ml > mid) return query(nown << 1 | 1, mid + 1, r, ml, mr);
	if(mr <= mid) return query(nown << 1, l, mid, ml, mr);
	NODE ans, tmpx= query(nown << 1, l, mid, ml, mr), tmpy= query(nown << 1 | 1, mid + 1, r, ml, mr);
	ans.sum= tmpx.sum + tmpy.sum;
	ans.lans= max(tmpx.lans, tmpx.sum + tmpy.lans);
	ans.rans= max(tmpy.rans, tmpy.sum + tmpx.rans);
	ans.ans= max(max(tmpx.ans, tmpy.ans), tmpx.rans + tmpy.lans);
	return ans;
}
void update(int nown, int l, int r, int md, int c) {
	if(l == r) {
		node[nown].ans= node[nown].lans= node[nown].rans= node[nown].sum= c;
		return;
	}
	int mid= (l + r) >> 1;
	if(mid >= md)
		update(nown << 1, l, mid, md, c);
	else
		update(nown << 1 | 1, mid + 1, r, md, c);
	pushu(nown);
	return;
}
int main() {
	n= read();
	for(int i= 1; i <= n; i++) a[i]= read();
	build(1, 1, n);
	m= read();
	int tmpx, tmpy, tmpz;
	for(int i= 1; i <= m; i++) {
		tmpx= read(), tmpy= read(), tmpz= read();
		if(tmpx == 1)
			printf("%d\n", query(1, 1, n, tmpy, tmpz).ans);
		else
			update(1, 1, n, tmpy, tmpz);
	}
	return 0;
}