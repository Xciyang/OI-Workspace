#pragma GCC optimize(1)
#pragma G++ optimize(1)
#pragma GCC optimize(2)
#pragma G++ optimize(2)
#pragma GCC optimize(3)
#pragma G++ optimize(3)
#pragma GCC optimize(4)
#pragma G++ optimize(4)
#pragma GCC optimize(5)
#pragma G++ optimize(5)
#pragma GCC optimize(6)
#pragma G++ optimize(6)
#pragma GCC optimize(7)
#pragma G++ optimize(7)
#pragma GCC optimize(8)
#pragma G++ optimize(8)
#pragma GCC optimize(9)
#pragma G++ optimize(9)
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")

#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
int n, k;
unsigned int sumx[500005], a[500005];
long long ans;
struct TRIE {
	struct NODE {
		NODE *ch[2];
		int sign1, sign2;
	} rt[500005];
	NODE node[20000007];
	inline NODE *newNODE() {
		static int p = 0;
		return &node[++p];
	}
	inline NODE *newNODE(NODE *n) {
		NODE *p = newNODE();
		if(n) *p = *n;
		return p;
	}
	struct INFO {
		long long x;
		int k;
	};
	void build(int x, int id, int lid) {
		NODE *p = &(rt[id] = rt[lid]);
		for(int i = 32, ch; i >= 0; i--) {
			ch = (x >> i) & 1;
			p->ch[ch] = newNODE(p->ch[ch]);
			p = p->ch[ch], p->sign1 = max(p->sign1, id);
		}
		p->sign2 = id;
		return;
	}
	INFO query(int x, int l, int r) {
		if(l < 1 || r < 1 || l > r) return INFO{0, 0};
		NODE *p = &rt[r];
		long long ans = 0;
		for(int i = 32, ch; i >= 0; i--) {
			ch = (x >> i) & 1;
			if(p->ch[ch ^ 1] && p->ch[ch ^ 1]->sign1 >= l) {
				ans |= (1ll << i);
				p = p->ch[ch ^ 1];
			}
			else if(p->ch[ch] && p->ch[ch]->sign1 >= l) {
				p = p->ch[ch];
			}
			else {
				break;
			}
		}
		return INFO{ans, p->sign2};
	}
} trie;
struct NODE {
	long long x;
	int l, r, k, k2;
	inline int operator<(const NODE &n2) const {
		return x < n2.x;
	}
};
inline long long read() {
	long long e = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		e = e * 10 + ch - '0';
		ch = getchar();
	}
	return e * f;
}
priority_queue< NODE > qu;
signed main() {
	n= read(), k= read();
	for(register int i = 1; i <= n; i++) a[i] = read(), sumx[i] = sumx[i - 1] ^ a[i], trie.build(sumx[i], i, i - 1);
	register TRIE::INFO a;
	for(register int i = 1; i <= n; i++) {
		a = trie.query(sumx[i - 1], i, n);
		if(a.x) qu.push(NODE{a.x, i, n, a.k, i});
	}
	register NODE p;
	for(register int i = 1; i <= k; i++) {
		p = qu.top(), qu.pop();
		ans += p.x;
		a = trie.query(sumx[p.k2 - 1], p.l, p.k - 1);
		if(a.x) qu.push(NODE{a.x, p.l, p.k - 1, a.k, p.k2});
		a = trie.query(sumx[p.k2 - 1], p.k + 1, p.r);
		if(a.x) qu.push(NODE{a.x, p.k + 1, p.r, a.k, p.k2});
	}
	cout << ans << endl;
	return 0;
}
