#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
#define int long long
int n, k, sumx[500005], a[500005];
priority_queue< int, vector< int >, less< int > > qu;
long long ans;
struct TRIE {
	struct NODE {
		NODE *ch[2];
		int signs;
		NODE() {
			ch[0]= ch[1]= 0x00, signs= 0;
		}
		NODE(NODE *fa) {
			ch[0]= fa->ch[0], ch[1]= fa->ch[1], signs= fa->signs;
		}
	} MNODE[500005];
	void insert(int w, int num) {
		NODE *p= &(MNODE[w]= MNODE[w - 1]);
		for(int i= 31, ch; i > -1; i--) {
			ch= (num >> i) & 1;
			if(!p->ch[ch])
				p->ch[ch]= new NODE();
			else
				p->ch[ch]= new NODE(p->ch[ch]);
			p->signs= w;
		}
		return;
	}
	int find(int w, int num, int g) {
		int findg= 0;
		return findg;
	}
};
signed main() {
	cin >> n >> k;
	for(int i= 1; i <= n; i++) cin >> a[i], sumx[i]= sumx[i - 1] ^ a[i];
	for(int i= 1; i <= n; i++)
		for(int j= i; j <= n; j++) qu.push(sumx[i - 1] ^ sumx[j]);
	for(int i= 1; i <= k; i++) ans+= qu.top(), qu.pop();
	cout << ans << endl;
	return 0;
}
// baoli
