#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
const int MAXN= 100005;
using namespace std;
int n, a[MAXN], js[MAXN], os[MAXN], b[MAXN], c[MAXN];
long long cnt, ans1, ans2;
int absi(int x) {
	return x < 0 ? -x : x;
}
int check() {
	for(int i= 1; i <= n; i++)
		if(b[i] != c[i]) return b[i] < c[i];
	return 1;
}
long long bestans= LLONG_MAX;
int nowa[MAXN], besta[MAXN], wp[MAXN];
int check2(int k) {
	for(int i= 1; i <= k; i++)
		if(nowa[i] != besta[i]) return nowa[i] < besta[i];
	return 0;
}
void dfs(int nown, long long nowans) {
	if(nowans > bestans) return;
	if(nowans == bestans && !check2(nown - 1)) return;
	if(nown == n + 1) {
		bestans= nowans;
		memcpy(besta, nowa, sizeof(besta));
		return;
	}
	if(nown & 1) {
		for(int i= 1; i <= js[0]; i++) {
			if(wp[js[i]]) continue;
			nowa[nown]= a[js[i]], wp[js[i]]= 1;
			dfs(nown + 1, nowans + absi(js[i] - nown));
			wp[js[i]]= 0;
		}
	}
	else {
		for(int i= 1; i <= os[0]; i++) {
			if(wp[os[i]]) continue;
			nowa[nown]= a[os[i]], wp[os[i]]= 1;
			dfs(nown + 1, nowans + absi(os[i] - nown));
			wp[os[i]]= 0;
		}
	}
}
void dfs2(int nown, long long nowans) {
	if(nowans > bestans) return;
	if(nown == n + 1) {
		if(nowans == bestans && !check2(n)) return;
		bestans= nowans;
		memcpy(besta, nowa, sizeof(besta));
		return;
	}
	if(nown & 1) {
		for(int i= 1; i <= os[0]; i++) {
			if(wp[os[i]]) continue;
			nowa[nown]= a[os[i]], wp[os[i]]= 1;
			dfs(nown + 1, nowans + absi(os[i] - nown));
			wp[os[i]]= 0;
		}
	}
	else {
		for(int i= 1; i <= js[0]; i++) {
			if(wp[js[i]]) continue;
			nowa[nown]= a[js[i]], wp[js[i]]= 1;
			dfs(nown + 1, nowans + absi(js[i] - nown));
			wp[js[i]]= 0;
		}
	}
}
struct NODE {
	int lasti, aa;
} node[MAXN];
void sort(int x, int y) {
begin:
	for(int i= 1; i <= x; i++) {
		for(int j= i + 1; j <= x; j++) {
			if(i < j && node[i].lasti < node[j].lasti && node[i].lasti >= j * 2 - y && node[i].aa > node[j].aa) {
				// cerr << "change" << node[i].aa << ' ' << node[j].aa << endl;
				swap(node[i], node[j]);
				goto begin;
			}
			if(i < j && node[i].lasti < node[j].lasti && node[j].lasti <= i * 2 - y && node[i].aa > node[j].aa) {
				// cerr << "change" << node[i].aa << ' ' << node[j].aa << endl;
				swap(node[i], node[j]);
				goto begin;
			}
		}
	}
	return;
}
void init1() {
	if(!(n & 1) || (js[0] & 1)) {
		cnt= 0;
		for(int i= 1, idptr= 1; i <= js[0] && idptr <= n; i++, idptr+= 2) {
			cnt+= absi(js[i] - idptr);
			node[i].lasti= js[i], node[i].aa= a[js[i]];
		}
		// sort(node + 1, node + js[0] + 1);
		sort(js[0], 1);
		for(int i= 1, idptr= 1; i <= js[0] && idptr <= n; i++, idptr+= 2) b[idptr]= node[i].aa;
		for(int i= 1, idptr= 2; i <= os[0] && idptr <= n; i++, idptr+= 2) {
			cnt+= absi(os[i] - idptr);
			node[i].lasti= os[i], node[i].aa= a[os[i]];
		}
		// sort(node + 1, node + os[0] + 1);
		sort(os[0], 0);

		for(int i= 1, idptr= 2; i <= os[0] && idptr <= n; i++, idptr+= 2) b[idptr]= node[i].aa;
		ans1= cnt;
	}
	else {
		ans1= LLONG_MAX;
	}
	return;
}
void init2() {
	if(!(n & 1) || (os[0] & 1)) {
		cnt= 0;
		for(int i= 1, idptr= 1; i <= os[0] && idptr <= n; i++, idptr+= 2) {
			cnt+= absi(os[i] - idptr);
			node[i].lasti= os[i], node[i].aa= a[os[i]];
		}
		sort(os[0], 1);
		for(int i= 1, idptr= 1; i <= os[0] && idptr <= n; i++, idptr+= 2) c[idptr]= node[i].aa;
		for(int i= 1, idptr= 2; i <= js[0] && idptr <= n; i++, idptr+= 2) {
			cnt+= absi(js[i] - idptr);
			node[i].lasti= js[i], node[i].aa= a[js[i]];
		}
		sort(js[0], 0);
		for(int i= 1, idptr= 2; i <= js[0] && idptr <= n; i++, idptr+= 2) c[idptr]= node[i].aa;
		ans2= cnt;
	}
	else {
		ans2= LLONG_MAX;
	}
	return;
}
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) {
		cin >> a[i];
		if(a[i] & 1)
			js[++js[0]]= i;
		else
			os[++os[0]]= i;
	}
	if(n == 1) {
		cout << a[1] << endl;
		return 0;
	}
	init1();
	init2();
	if(ans1 < ans2) {
		for(int i= 1; i <= n; i++) cout << b[i] << ' ';
		cout << endl;
	}
	else if(ans1 > ans2) {
		for(int i= 1; i <= n; i++) cout << c[i] << ' ';
		cout << endl;
	}
	else if(check()) {
		for(int i= 1; i <= n; i++) cout << b[i] << ' ';
		cout << endl;
	}
	else {
		for(int i= 1; i <= n; i++) cout << c[i] << ' ';
		cout << endl;
	}
	return 0;
}