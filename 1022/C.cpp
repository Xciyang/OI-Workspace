#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, q, a[100005], bestans, cnt, b[100005];
inline int op(int x, int y) {
	if(q == 1) return x & y;
	if(q == 2) return x ^ y;
	return x | y;
}
struct TRIE {
	struct NODE {
		NODE *nxt[2];
		NODE() {
			nxt[0]= nxt[1]= 0;
		}
	} MNODE;
	void insert(int x) {
		NODE *p= &MNODE;
		for(int i= 23, c; i >= 0; i--) {
			c= ((x >> i) & 1);
			if(!p->nxt[c]) p->nxt[c]= new NODE();
			p= p->nxt[c];
		}
		return;
	}
	int query1(int x) {
		NODE *p= &MNODE;
		int res= 0;
		for(int i= 23, c; i >= 0; i--) {
			c= ((x >> i) & 1);
			if(!c) {
				if(p->nxt[1] || !p->nxt[0]) break;
				p= p->nxt[0];
			}
			if(c == 1) {
				if(p->nxt[1])
					p= p->nxt[1], res+= (1 << i);
				else if(p->nxt[0])
					p= p->nxt[0];
				else
					break;
			}
		}
		return res;
	}
	int query2(int x) {
		NODE *p= &MNODE;
		int res= 0;
		for(int i= 23, c; i >= 0; i--) {
			c= ((x >> i) & 1);
			if(p->nxt[c ^ 1])
				p= p->nxt[c ^ 1], res+= (1 << i);
			else if(p->nxt[c])
				p= p->nxt[c];
			else
				break;
		}
		return res;
	}

} trie;
inline int change(int x) {
	for(int i= 23; i >= 0; i--) {
		if((x >> i) & 1) {
			for(int j= i; j >= 0; j--) {
				if(!((x >> j) & 1)) break;
				x^= (1 << j);
			}
			break;
		}
	}
	return x;
}
int main() {
	cin >> n >> q;
	for(int i= 1; i <= n; i++) cin >> a[i];
	if(n <= 1000) {
		for(int i= 1; i <= n; i++) {
			for(int j= i + 1; j <= n; j++) {
				int res= op(a[i], a[j]);
				if(res > bestans) bestans= res, cnt= 0;
				if(res == bestans) ++cnt;
			}
		}
		cout << bestans << ' ' << cnt << endl;
	}
	else if(q == 1) {
		sort(a + 1, a + n + 1);
		for(int i= 1; i <= n; i++) {
			int res= trie.query1(a[i]);
			if(res > bestans) bestans= res, cnt= 0;
			if(res == bestans) ++cnt;
			trie.insert(a[i]);
		}
		trie.MNODE.nxt[0]= trie.MNODE.nxt[1]= 0;
		for(int i= n; i; i--) {
			int res= trie.query1(a[i]);
			if(res > bestans) bestans= res, cnt= 0;
			if(res == bestans) ++cnt;
			trie.insert(a[i]);
		}
		cout << bestans << ' ' << cnt << endl;
	}
	else if(q == 2) {
		for(int i= 1; i <= n; i++) trie.insert(a[i]);
		for(int i= 1; i <= n; i++) {
			int res= trie.query2(a[i]);
			if(res > bestans) bestans= res, cnt= 0;
			if(res == bestans) ++cnt;
		}
		cout << bestans << ' ' << cnt / 2 << endl;
	}
	else if(q == 3) {
		for(int i= 1; i <= n; i++) trie.insert(a[i]);
		for(int i= 1; i <= n; i++) {
			int x= change(a[i]);
			int res= ((trie.query2(x) ^ x) | a[i]);
			res= max(res, ((trie.query2(a[i]) ^ a[i]) | a[i]));
			if(res > bestans) bestans= res, cnt= 0;
			if(res == bestans) ++cnt;
		}
		cout << bestans << ' ' << cnt / 2 << endl;
	}
	return 0;
}

/*
5 1
1 4 5 7 9

5 1
1 4 4 4 5

*/