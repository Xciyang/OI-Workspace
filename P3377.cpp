#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, tmpx, tmpy, tmpz, tmps;
int dui[100010], l[100010], r[100010], v[100010], d[100010];
#define swap(a, b) (tmps= (a), (a)= (b), (b)= tmps)
int inline read() {
	int x= 0, f= 1;
	char ch= getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x= x * 10 + ch - '0';
		ch= getchar();
	}
	return x * f;
}
int merge(int x, int y) {
	if(!x || !y) return x + y;
	if(v[x] > v[y] || (v[x] == v[y] && x > y)) swap(x, y);
	r[x]= merge(r[x], y), dui[r[x]]= dui[l[x]]= dui[x]= x;
	if(d[l[x]] < d[r[x]]) swap(l[x], r[x]);
	d[x]= d[r[x]] + 1;
	return x;
}
inline int getdui(int x) {
	return dui[x] == x ? x : dui[x]= getdui(dui[x]);
}
inline void pop(int x) {
	v[x]= -1, dui[r[x]]= r[x], dui[l[x]]= l[x], dui[x]= merge(r[x], l[x]);
	return;
}
int main() {
	n= read(), m= read(), d[0]= -1;
	for(int i= 1; i <= n; i++) scanf("%d", v + i), dui[i]= i;
	for(int i= 1; i <= m; i++) {
		tmpx= read();
		if(tmpx == 1) {
			tmpy= read(), tmpz= read();
			if(v[tmpy] == -1 || v[tmpz] == -1) continue;
			tmpy= getdui(tmpy), tmpz= getdui(tmpz);
			if(tmpy != tmpz) dui[tmpy]= dui[tmpz]= merge(tmpy, tmpz);
		}
		else {
			tmpy= read();
			if(v[tmpy] == -1)
				printf("-1\n");
			else
				printf("%d\n", v[getdui(tmpy)]), pop(getdui(tmpy));
		}
	}
	return 0;
}