#include <bits/stdc++.h>
#define maxn 132010
#define ls rt << 1
#define rs rt << 1 | 1
using namespace std;
struct Seg {
	int l, r, cov, tag;
} seg[maxn << 2];
int ans[maxn], n = maxn;
char s[20];

void get(int &l, int &r) {
	char c = getchar();
	for(; c != '(' && c != '['; c = getchar())
		;
	int w = c == '(';
	l = 0;
	for(; !isdigit(c); c = getchar())
		;
	for(; isdigit(c); c = getchar()) l = (l << 1) + (l << 3) + (c ^ 48);
	l <<= 1;
	l += w, r = 0;
	for(; !isdigit(c); c = getchar())
		;
	for(; isdigit(c); c = getchar()) r = (r << 1) + (r << 3) + (c ^ 48);
	r <<= 1;
	for(; c != ')' && c != ']'; c = getchar())
		;
	r -= c == ')';
}

void pushdown(int rt) {
	if(seg[rt].cov != -1) {
		seg[ls].cov = seg[rs].cov = seg[rt].cov;
		seg[ls].tag = seg[rs].tag = 0;
		seg[rt].cov = -1;
	}
	if(seg[rt].tag) {
		seg[ls].tag ^= 1, seg[rs].tag ^= 1;
		seg[rt].tag = 0;
	}
}

void build(int rt, int l, int r) {
	seg[rt].l = l, seg[rt].r = r, seg[rt].cov = -1;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
}

void update(int rt, int l, int r, int k) {
	if(seg[rt].l > r || seg[rt].r < l || l > r) return;
	if(seg[rt].l >= l && seg[rt].r <= r) {
		if(k != 2)
			seg[rt].cov = k, seg[rt].tag = 0;
		else
			seg[rt].tag ^= 1;
		return;
	}
	pushdown(rt);
	update(ls, l, r, k), update(rs, l, r, k);
}

void query(int rt) {
	if(seg[rt].l == seg[rt].r) {
		ans[seg[rt].l] = seg[rt].cov == -1 ? 0 : seg[rt].cov ^ seg[rt].tag;
		return;
	}
	pushdown(rt);
	query(ls), query(rs);
}

void print() {
	query(1);
	int flag = 0, Empty = 0;
	for(int i = 0; i <= n; ++i) {
		if(ans[i] && !flag) {
			flag = Empty = 1;
			if(i & 1)
				printf("(%d,", (i - 1) >> 1);
			else
				printf("[%d,", i >> 1);
		}
		if(!ans[i] && flag) {
			flag = 0;
			if(i & 1)
				printf("%d] ", (i - 1) >> 1);
			else
				printf("%d) ", i >> 1);
		}
	}
	if(!Empty) puts("empty set");
}

int main() {
	build(1, 0, n);
	while(scanf("%s", s) != EOF) {
		int l, r;
		get(l, r);
		if(s[0] == 'U')
			update(1, l, r, 1);
		else if(s[0] == 'I')
			update(1, 0, l - 1, 0), update(1, r + 1, n, 0);
		else if(s[0] == 'D')
			update(1, l, r, 0);
		else if(s[0] == 'C')
			update(1, 0, n, 2), update(1, 0, l - 1, 0), update(1, r + 1, n, 0);
		else
			update(1, l, r, 2);
	}
	print();
	return 0;
}