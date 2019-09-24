#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <stdlib.h>
using namespace std;
#define GUILTY 1
#define WEEK 2
struct ZY {
	int typ, k, c;
} zys[105];
string tmps, tmpms;
map< string, int > pep;
struct INFO {
	int xq, yd[21], bxq[21];
} nown;
int m, n, p;
string xqj;
vector< int > v[25];
string week[]= {"Monday", "Tuesday", "Wednesday", "Thursday", "Firday", "Saturday", "Sunday"};
string peo[25];
int Judge(int x) {
	for(int i= 0; i < v[x].size(); i++) {
		switch(zys[v[x][i]].typ) {
			case GUILTY: {
				if(nown.yd[zys[v[x][i]].k] && nown.yd[zys[v[x][i]].k] != zys[v[x][i]].c) return 0;
				nown.yd[zys[v[x][i]].k]= zys[v[x][i]].c;
				break;
			}
			case WEEK: {
				if(nown.xq && nown.xq != zys[v[x][i]].k) return 0;
				if(nown.bxq[zys[v[x][i]].k]) return 0;
				nown.xq= zys[v[x][i]].k;
				break;
			}
			default: break;
		}
	}
	return 1;
}
int Judge2(int x) {
	for(int i= 0; i < v[x].size(); i++) {
		switch(zys[v[x][i]].typ) {
			case GUILTY: {
				if(nown.yd[zys[v[x][i]].k] && nown.yd[zys[v[x][i]].k] != -zys[v[x][i]].c) return 0;
				nown.yd[zys[v[x][i]].k]= -zys[v[x][i]].c;
				break;
			}
			case WEEK: {
				if(nown.xq && nown.xq == zys[v[x][i]].k) return 0;
				nown.bxq[zys[v[x][i]].k]= 1;
				break;
			}
			default: break;
		}
	}
	return 1;
}
int zfg, flag;
int szf[35];
void DFS(int np, int hadz) {
	if(hadz == n + 1) {
		for(int i= np; i <= m; i++)
			if(!Judge(i)) return;
        flag= 1;
		int cnt= 0, ans= 0, bs= 0;
		for(int i= 1; i <= m; i++) {
			if(nown.yd[i] == 1) ++cnt, ans= i;
			if(nown.yd[i] == -1) ++bs, szf[i]= 1;
		}
		if(bs == m - 1) {
			for(int i= 1; i <= m; i++)
				if(nown.yd[i] == 0) ans= i;
			cnt= 1;
		}
		if(cnt == 1 && zfg && ans != zfg) {
			cout << "Cannot Determine" << endl;
			exit(0);
		}
		if(cnt == 1) zfg= ans;
		return;
	}
	if(n - hadz > m - np) return;
	INFO lasti= nown;
	if(Judge(np)) DFS(np + 1, hadz);
	nown= lasti;
	if(Judge2(np)) DFS(np + 1, hadz + 1);
	nown= lasti;
	return;
}
int main() {
	cin >> m >> n >> p;
	for(int i= 1; i <= m; i++) cin >> peo[i], pep[peo[i]]= i;
	for(int i= 1; i <= p; i++) {
		cin >> tmps;
		getline(cin, tmpms);
		tmps.pop_back();
		while(!tmpms.empty() && tmpms[tmpms.size() - 1] == '\r' || tmpms[tmpms.size() - 1] == '\n') tmpms.pop_back();

		if(tmpms == " I am guilty.") {
			zys[i]= ZY{GUILTY, pep[tmps], 1};
			v[pep[tmps]].push_back(i);
			continue;
		}
		if(tmpms == " I am not guilty.") {
			zys[i]= ZY{GUILTY, pep[tmps], -1};
			v[pep[tmps]].push_back(i);
			continue;
		}
		int flag= 0;
		for(int j= 0; j < 7; j++) {
			if(tmpms == " Today is " + week[j] + ".") {
				zys[i]= ZY{WEEK, j + 1, 0};
				v[pep[tmps]].push_back(i);
				break;
			}
		}
		if(flag) continue;
		for(int j= 1; j <= m; j++) {
			if(tmpms == " " + peo[j] + " is guilty.") {
				zys[i]= ZY{GUILTY, pep[peo[j]], 1};
				v[pep[tmps]].push_back(i);
				break;
			}
			if(tmpms == " " + peo[j] + " is not guilty.") {
				zys[i]= ZY{GUILTY, pep[peo[j]], -1};
				v[pep[tmps]].push_back(i);
				break;
			}
		}
	}
	DFS(1, 1);
	if(zfg) {
		cout << peo[zfg] << endl;
		return 0;
	}
	for(int i= 1; i <= p; i++) {
		if(flag && !szf[i]) {
			cout << "Cannot Determine" << endl;
			return 0;
		}
	}
	cout << "Impossible" << endl;
	return 0;
}