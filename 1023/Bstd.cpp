#include <bits/stdc++.h>
#define ci const int &
using namespace std;
struct node {
	int l, r, tt, be, ed, lp, ls, tg;
} t[800010];
int n, m, a[200010];
vector< int > num[200010];
void Upd(ci x) {
	t[x].be= t[x << 1].be, t[x].ed= t[x << 1 | 1].ed;
	if(t[x << 1].tg && t[x << 1 | 1].tg) {
		t[x].tt= 0;
		if(!(t[x << 1].ed + t[x << 1 | 1].be))
			t[x].tg= 1, t[x].lp= t[x].ls= t[x << 1].lp + t[x << 1 | 1].ls;
		else
			t[x].tg= 0, t[x].lp= t[x << 1].lp, t[x].ls= t[x << 1 | 1].ls;
	}
	else if(t[x << 1].tg) {
		t[x].tg= 0, t[x].tt= t[x << 1 | 1].tt;
		if(t[x << 1].ed && !(t[x << 1].ed + t[x << 1 | 1].be))
			t[x].lp= t[x << 1].ls + t[x << 1 | 1].lp, t[x].ls= t[x << 1 | 1].ls;
		else
			t[x].lp= t[x << 1].lp, t[x].ls= t[x << 1 | 1].ls, t[x].tt= t[x << 1 | 1].tt + (t[x << 1 | 1].lp >> 1);
	}
	else if(t[x << 1 | 1].tg) {
		t[x].tg= 0;
		if(t[x << 1].ed && !(t[x << 1].ed + t[x << 1 | 1].be))
			t[x].lp= t[x << 1].lp, t[x].ls= t[x << 1 | 1].ls + t[x << 1].ls, t[x].tt= t[x << 1].tt;
		else
			t[x].lp= t[x << 1].lp, t[x].ls= t[x << 1 | 1].ls, t[x].tt= t[x << 1].tt + (t[x << 1].ls >> 1);
	}
	else {
		t[x].tg= 0, t[x].lp= t[x << 1].lp, t[x].ls= t[x << 1 | 1].ls;
		if(t[x << 1].ed && !(t[x << 1].ed + t[x << 1 | 1].be))
			t[x].tt= t[x << 1].tt + t[x << 1 | 1].tt + (t[x << 1].ls + t[x << 1 | 1].lp >> 1);
		else
			t[x].tt= t[x << 1].tt + t[x << 1 | 1].tt + (t[x << 1].ls >> 1) + (t[x << 1 | 1].lp >> 1);
	}
}
void Build(ci x, ci l, ci r) {
	t[x].l= l, t[x].r= r;
	if(l == r) return (void)(t[x].be= t[x].ed= t[x].tg= t[x].lp= t[x].ls= 1);
	int mid= l + r >> 1;
	Build(x << 1, l, mid), Build(x << 1 | 1, mid + 1, r), Upd(x);
}
void Change(ci x, ci id, ci v) {
	if(t[x].l == t[x].r) return (void)(t[x].be= t[x].ed= v, t[x].tg= !!v);
	int mid= t[x].l + t[x].r >> 1;
	id <= mid ? Change(x << 1, id, v) : Change(x << 1 | 1, id, v), Upd(x);
}
int main() {
	scanf("%d%d", &n, &m), Build(1, 1, n);
	for(int i= 1; i <= n; ++i) scanf("%d", &a[i]), num[a[i]].push_back(i);
	for(int i= 1; i <= m; ++i) {
		for(int j= 0; j < num[i - 1].size(); ++j) Change(1, num[i - 1][j], -1);
		for(int j= 0; j < num[i].size(); ++j) Change(1, num[i][j], 0);
		if(!num[i].size()) {
			printf("-1 ");
			continue;
		}
		if(t[1].be && !(t[1].be + t[1].ed))
			printf("%d ", n - num[i].size() + t[1].tt + (t[1].lp + t[1].ls >> 1));
		else
			printf("%d ", n - num[i].size() + t[1].tt + (t[1].lp >> 1) + (t[1].ls >> 1));
	}
	return 0;
}
