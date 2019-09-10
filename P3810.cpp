#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, m, cnt, nn, ans[100005];
struct ELE {
	int a, b, c, w, ans;
	bool operator<(const ELE &e2) const {
		return a == e2.a ? b == e2.b ? c < e2.c : b < e2.b : a < e2.a;
	}
	bool operator==(const ELE &e2) const {
		return a == e2.a && b == e2.b && c == e2.c;
	}
} a[100005], b[100005];
int bitr[200005];
#define lowb(x) ((x) & -(x))
void update(int x, int c) {
	while(x <= m) bitr[x]+= c, x+= lowb(x);
	return;
}
void query(int x, int &res) {
	while(x) res+= bitr[x], x-= lowb(x);
	return;
}
void msort(int l, int r) {
	if(l == r) return;
	int mid= (l + r) >> 1;
	msort(l, mid), msort(mid + 1, r);
	int ll= l, lm= mid + 1, p= l;
	while(ll <= mid && lm <= r) b[ll].b <= b[lm].b ? (update(b[ll].c, b[ll].w), a[p++]= b[ll++]) : (query(b[lm].c, b[lm].ans), a[p++]= b[lm++]);
	while(ll <= mid) update(b[ll].c, b[ll].w), a[p++]= b[ll++];
	while(lm <= r) query(b[lm].c, b[lm].ans), a[p++]= b[lm++];
	for(int i= l; i <= mid; i++) update(b[i].c, -b[i].w);
	for(int i= l; i <= r; i++) b[i]= a[i];
	return;
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) cin >> a[i].a >> a[i].b >> a[i].c;
	sort(a + 1, a + n + 1);
	for(int i= 1; i <= n; i++) {
		if(++cnt, a[i] == a[i + 1]) continue;
		b[++nn]= a[i], b[nn].w= cnt, cnt= 0;
	}
	msort(1, nn);
	for(int i= 1; i <= nn; i++) ans[b[i].ans + b[i].w - 1]+= b[i].w;
	for(int i= 0; i < n; i++) cout << ans[i] << endl;
	return 0;
}