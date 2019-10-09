#include <iostream>
#include <stdio.h>
#include <map>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxk= 46;
const int maxNM= 40;

long long mj[maxk][4], ys[maxNM];
int k, n, m, ans, bestans, chos[maxk], flag[maxk], bestanss[maxk];
char tmpc;
int trydfs(int nowhang, int lastlie, int nowt) {
	if(nowhang == n + 1) {
#ifdef MAKE_DATA
		if(!bestans) bestans= nowt;
		if(nowt > bestans) return 1;
		cout << nowt << endl;
		int ls[maxk];
		memcpy(ls, chos, sizeof(ls));
		sort(ls, ls + nowt);
		for(int i= 0; i < nowt; i++) cout << ls[i] << ' ';
		cout << endl << " --- " << endl;
#endif
		return 1;
	}
	int nowlie= m;
	for(; nowlie; nowlie--)
		if((1LL << nowlie) & ys[nowhang]) break;
	if(!nowlie) return trydfs(nowhang + 1, m, nowt);
	for(int i= 0, tmpi; i < nowt; i++) {
		tmpi= chos[i];
		long long l;
		for(int j= 1; j <= 3; j++) {
			l= (mj[tmpi][j] >> (m - nowlie));
			if((l & ys[nowhang + j - 1]) != l) goto nexti;
		}
		for(int j= 1; j <= 3; j++) l= (mj[tmpi][j] >> (m - nowlie)), ys[nowhang + j - 1]^= l;
#ifdef MAKE_DATA
		trydfs(nowhang, nowlie, nowt);
#else
		if(trydfs(nowhang, nowlie, nowt)) return 1;
#endif
		for(int j= 1; j <= 3; j++) l= (mj[tmpi][j] >> (m - nowlie)), ys[nowhang + j - 1]^= l;
	nexti:;
	}
	if(nowt < ans) {
		for(int i= 1; i <= k; i++) {
			if(flag[i]) continue;
			long long l;
			for(int j= 1; j <= 3; j++) {
				l= (mj[i][j] >> (m - nowlie));
				if((l & ys[nowhang + j - 1]) != l) goto nexti2;
			}
			for(int j= 1; j <= 3; j++) l= (mj[i][j] >> (m - nowlie)), ys[nowhang + j - 1]^= l;
			chos[nowt]= i, flag[i]= 1;
#ifdef MAKE_DATA
			trydfs(nowhang, nowlie, nowt + 1);
#else
			if(trydfs(nowhang, nowlie, nowt + 1)) return 1;
#endif
			flag[i]= 0;
			for(int j= 1; j <= 3; j++) l= (mj[i][j] >> (m - nowlie)), ys[nowhang + j - 1]^= l;
		nexti2:;
		}
	}
	return 0;
}
void IDDFS() {
	for(ans= 1; ans <= n; ans++)
		if(trydfs(1, m, 0)) 
			if(!bestans){
				bestans= ans;
				memcpy(bestanss, chos, sizeof(bestanss));
			} 
#ifndef MAKE_DATA
	ans= -1;
#endif
	return;
}
signed main() {
	cin >> k >> n >> m;
	for(int i= 1; i <= k; i++)
		for(int j= 1; j <= 3; j++)
			for(int l= 1; l <= 3; l++) cin >> tmpc, mj[i][j]|= ((long long)(tmpc == '*') << (m - l + 1));
	for(int i= 1; i <= n; i++)
		for(int j= m; j; j--) cin >> tmpc, ys[i]|= ((long long)(tmpc == '*') << j);
	IDDFS();
#ifndef MAKE_DATA
	cout << bestans << endl;
	sort(bestanss, bestanss + bestans);
	for(int i= 0; i < bestans; i++) cout << bestanss[i] << ' ';
	cout << endl;
#endif
	return 0;
}