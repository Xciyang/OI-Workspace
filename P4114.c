#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int n, tmpx, tmpy, tmpz, edptr, head[10004], tmpt;
#define swap(a, b) (tmpt= (a), (a)= (b), (b)= tmpt)

struct edge {
	int to, nexty, dis;
} eds[20005];
void add(int a, int b, int c) {
	eds[edptr].to= b, eds[edptr].nexty= head[a], eds[edptr].dis= c;
	head[a]= edptr++;
	return;
}
int fa[10004], siz[10004], hson[10004], p[10004], deep[10004];
void dfs1(int nown, int f) {
	deep[nown]= deep[f] + 1, fa[nown]= f, siz[nown]= 1;
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == f) continue;
		p[to]= eds[i].dis;
		dfs1(to, nown);
		siz[nown]+= siz[to];
		if(siz[to] > siz[hson[nown]]) hson[nown]= to;
	}
	return;
}
int id[10004], iptr, top[10004], va[10004];
void dfs2(int nown, int f) {
	id[nown]= ++iptr, top[nown]= f, va[iptr]= p[nown];
	if(hson[nown]) dfs2(hson[nown], f);
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == fa[nown] || to == hson[nown]) continue;
		dfs2(to, to);
	}
	return;
}
struct NODE {
	int v;
} node[10004 << 2];
int maxi(int a, int b) {
	return a > b ? a : b;
}
void build(int nown, int l, int r) {
	if(l == r) {
		node[nown].v= va[l];
		return;
	}
	int mid= (l + r) >> 1;
	build(nown << 1, l, mid), build(nown << 1 | 1, mid + 1, r);
	node[nown].v= maxi(node[nown << 1].v, node[nown << 1 | 1].v);
	return;
}
int query(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) return node[nown].v;
	int ans= 0, mid= (l + r) >> 1;
	if(mid >= ml) ans= maxi(ans, query(nown << 1, l, mid, ml, mr));
	if(mid < mr) ans= maxi(ans, query(nown << 1 | 1, mid + 1, r, ml, mr));
	return ans;
}
void update(int nown, int l, int r, int md, int c) {
	if(l == r) {
		node[nown].v= c;
		return;
	}
	int mid= (l + r) >> 1;
	if(mid >= md)
		update(nown << 1, l, mid, md, c);
	else
		update(nown << 1 | 1, mid + 1, r, md, c);
	node[nown].v= maxi(node[nown << 1].v, node[nown << 1 | 1].v);
	return;
}
int queryMax(int x, int y) {
	int ans= 0;
	while(top[x] != top[y]) {
		if(deep[top[x]] < deep[top[y]]) swap(x, y);
		ans= maxi(ans, query(1, 1, n, id[top[x]], id[x]));
		x= fa[top[x]];
	}
	if(id[x] > id[y]) swap(x, y);
	return maxi(ans, query(1, 1, n, id[x] + 1, id[y]));
}
char tmps[10];
int T;
int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		memset(head, 0, sizeof(head)), edptr= 2, iptr= 0;
		memset(hson, 0, sizeof(hson)), memset(siz, 0, sizeof(siz)), memset(fa, 0, sizeof(fa)), memset(deep, 0, sizeof(deep)), memset(deep, 0, sizeof(deep));
		for(int i= 1; i < n; i++) {
			scanf("%d%d%d", &tmpx, &tmpy, &tmpz);
			add(tmpx, tmpy, tmpz), add(tmpy, tmpx, tmpz);
		}
		dfs1(1, 0), dfs2(1, 1), build(1, 1, n);
		while(1) {
			scanf("%s", tmps);
			switch(tmps[0]) {
				case 'Q':
					scanf("%d%d", &tmpx, &tmpy);
					printf("%d\n", (tmpx == tmpy ? 0 : queryMax(tmpx, tmpy)));
					break;
				case 'C':
					scanf("%d%d", &tmpx, &tmpy);
					tmpx= deep[eds[tmpx << 1 ^ 1].to] < deep[eds[tmpx << 1].to] ? eds[tmpx << 1].to : eds[tmpx << 1 ^ 1].to;
					update(1, 1, n, id[tmpx], tmpy);
				default: break;
			}
			if(tmps[0] == 'D') break;
		}
	}

	return 0;
}