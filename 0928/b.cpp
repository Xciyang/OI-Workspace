#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
#include <algorithm>
const long long mod= 1e9 + 7;
using namespace std;
int n, k, w[100006];
long long frac[100006];
char tmps[100006];
struct TRIE {
	struct NODE {
		NODE *to[26];
		int flag;
	} MNODE;
	void insert(char *st, int len, int c) {
		NODE *p= &MNODE;
		for(int i= 0, ch; i < len; i++) {
			ch= st[i] - 'a';
			if(!p->to[ch]) p->to[ch]= new NODE();
			p= p->to[ch];
		}
		p->flag= c;
		return;
	}
	int search(char *st, int &cnt) {
		NODE *p= &MNODE;
		for(int i= 0, ch; st[i]; i++) {
			ch= st[i] - 'a';
			if(!p->to[ch]) return 0;
			p= p->to[ch];
			if(p->flag) {
				cnt+= i + 1;
				return p->flag;
			}
		}
		return 0;
	}
} trie;
int wp[100006], a[100006], pm, b[100006], wp2[100006], w2[100006];
int judge() {
	for(int i= 1; i <= k; i++) {
		if(w2[i] == b[i]) continue;
		return w2[i] > b[i] ? 1 : -1;
	}
	return 0;
}
void dfs2(int nown) {
	if(nown == k + 1) {
		int res= judge();
		if(res == 1) ++pm;
		return;
	}
	for(int i= 1; i <= k; i++) {
		if(wp2[i]) continue;
		wp2[i]= 1, b[nown]= w[i];
		dfs2(nown + 1);
		wp2[i]= 0, b[nown]= 0;
	}
	return;
}
void dfs(int nown, int last, int fl) {
	if(nown == k + 1) {
		if(fl) {
            dfs2(1);
			cout << pm << endl;
			exit(0);
		}
		pm+= frac[k];
		return;
	}
	for(int i= 1; i <= n; i++) {
		if(wp[i]) continue;
		a[nown]= i, wp[i]= 1;
		dfs(nown + 1, i + 1, fl && a[nown] == w[nown]);
		a[nown]= 0, wp[i]= 0;
	}
	return;
}
int main() {
	cin >> n >> k;
	frac[0]= 1;
	for(int i= 1; i <= n; i++) {
		cin >> tmps;
		trie.insert(tmps, strlen(tmps), i);
		frac[i]= frac[i - 1] * i % mod;
	}
	cin >> tmps;
	int cnt= 0, cnt2= 0;
	while(cnt2 < k) w[++cnt2]= trie.search(tmps + cnt, cnt);
	for(int i= 1; i <= k; i++) w2[i]= w[i];
	sort(w + 1, w + k + 1);
	dfs(1, 1, 1);
	return 0;
}
