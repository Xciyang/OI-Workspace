#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
int m, n, head[200001], edptr= 1, pmax, nptr, root[500001], rts, endr[500001];
struct tasks {
	int s, e, p;
} ts[200001];
struct edge {
	int to, nexty;
} eds[500001];
struct NODE {
	int ln, rn, num;
	long long sum;
} node[10000001];

inline void add(int a, int b) {
	eds[edptr].to= b, eds[edptr].nexty= head[a], head[a]= edptr++;
	return;
}
inline int absi(int a) {
	return a > 0 ? a : -a;
}
void update(int &nown, int fa, int c, int l, int r) {
	node[nown= ++nptr]= node[fa];
	node[nown].num+= (c > 0 ? 1 : -1), node[nown].sum+= c;
	if(l == r) return;
	int mid= (l + r) >> 1;
	if(absi(c) <= mid)
		update(node[nown].ln, node[fa].ln, c, l, mid);
	else
		update(node[nown].rn, node[fa].rn, c, mid + 1, r);
	return;
}
long long query(int nown, int c, int l, int r) {
	if(l == r) return l * c;
	int mid= (l + r) >> 1;
	if(c <= node[node[nown].ln].num) return query(node[nown].ln, c, l, mid);
	return query(node[nown].rn, c - node[node[nown].ln].num, mid + 1, r) + node[node[nown].ln].sum;
}
int main() {
	cin >> m >> n;
	for(int i= 1; i <= m; i++) {
		cin >> ts[i].s >> ts[i].e >> ts[i].p;
		add(ts[i].s, ts[i].p), add(ts[i].e + 1, -ts[i].p), pmax= max(pmax, ts[i].p);
	}
	for(int nown= 1; nown <= n; nown++) {
		for(int i= head[nown]; i; i= eds[i].nexty) ++rts, update(root[rts], root[rts - 1], eds[i].to, 1, pmax);
		endr[nown]= root[rts];
	}
	int xi, ai, bi, ci, ki;
	long long lasti= 1;
	for(int i= 1; i <= n; i++) {
		cin >> xi >> ai >> bi >> ci;
		ki= ((long long)ai * lasti + bi) % ci + 1;
		cout << (lasti= (ki >= node[endr[xi]].num ? node[endr[xi]].sum : query(endr[xi], ki, 1, pmax))) << endl;
	}
	return 0;
}