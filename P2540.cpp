#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
int T, n;
struct PAI {
	int num, col;
} ps[30];
#define SHUNZI 3
#define SANDAI 4
#define SIDAI 5
struct CP {
	int typ, l, r, k1, k2, siz;
	CP(int typ, int siz, int l= 0, int r= 0, int k1= 0, int k2= 0) {
		this->typ= typ, this->siz= siz, this->l= l, this->r= r, this->k1= k1, this->k2= k2;
	}
	inline int operator<(const CP &c2) const {
		return siz > c2.siz;
	}
};
int pai[20], bestans, us3[20], us2[20], us1[20];
vector< CP > v;
void dfs(int nown, int nowa, int ls) {
	if(nowa >= bestans) return;
	bestans= min(bestans, nowa + nown);
	if(!nown) return;
	int res= 0, us[4][20];
	memset(us, 0, sizeof(us));
	for(int i= 2; i <= 16; i++) res+= (pai[i] != 0);
	if(pai[15] && pai[16]) --res;
	bestans= min(bestans, nowa + res);
	for(int i= 14, cnt= 0; i >= 2; i--) {
		if(pai[i] < 1) continue;
		us[1][i]= us[1][i + 1] + 1;
		if(pai[i] < 2) continue;
		us[2][i]= us[2][i + 1] + 1;
		if(pai[i] < 3) continue;
		us[3][i]= us[3][i + 1] + 1;
	}
	for(int i= ls; i < v.size(); i++) {
		if(v[i].siz > nown) continue;
		switch(v[i].typ) {
			case SHUNZI: {
				if(v[i].r - v[i].l + 1 > us[v[i].k1][v[i].l]) break;
				for(int j= v[i].l; j <= v[i].r; j++) pai[j]-= v[i].k1;
				dfs(nown - v[i].siz, nowa + 1, i + 1);
				for(int j= v[i].l; j <= v[i].r; j++) pai[j]+= v[i].k1;
				break;
			}
			case SANDAI: {
				if(pai[v[i].l] < 3 || pai[v[i].k1] < v[i].r) break;
				pai[v[i].l]-= 3, pai[v[i].k1]-= v[i].r;
				dfs(nown - v[i].siz, nowa + 1, i + 1);
				pai[v[i].l]+= 3, pai[v[i].k1]+= v[i].r;
				break;
			}
			case SIDAI: {
				if(pai[v[i].l] < 4) break;
				if(pai[v[i].k1] < 1 || pai[v[i].k2] < 1) break;
				if(v[i].r == 2 && (pai[v[i].k1] < 2 || pai[v[i].k2] < 2)) break;
				if(v[i].r == 2 && v[i].k1 == v[i].k2 && pai[v[i].k1] < 4) break;
				if(v[i].r == 1 && v[i].k1 == v[i].k2 && pai[v[i].k1] < 2) break;
				pai[v[i].l]-= 4;
				pai[v[i].k1]-= v[i].r;
				pai[v[i].k2]-= v[i].r;
				dfs(nown - v[i].siz, nowa + 1, i + 1);
				pai[v[i].l]+= 4;
				pai[v[i].k1]+= v[i].r;
				pai[v[i].k2]+= v[i].r;
			}
			default: break;
		}
	}
	return;
}
int main() {
	scanf("%d%d", &T, &n);
	while(T--) {
		memset(pai, 0, sizeof(pai)), bestans= 0x3f3f3f3f;
		for(int i= 1; i <= n; i++) {
			scanf("%d%d", &ps[i].num, &ps[i].col);
			if(ps[i].num == 1) ps[i].num= 14;
			if(ps[i].num == 0) ps[i].num= ps[i].col + 14;
			++pai[ps[i].num];
		}
		memset(us3, 0, sizeof(us3)), memset(us2, 0, sizeof(us2)), memset(us1, 0, sizeof(us1));
		v.clear();
		for(int i= 14; i >= 3; i--) {
			if(pai[i] < 1) continue;
			us1[i]= us1[i + 1] + 1;
			if(pai[i] < 2) continue;
			us2[i]= us2[i + 1] + 1;
			if(pai[i] < 3) continue;
			us3[i]= us3[i + 1] + 1;
		}
		for(int i= 2; i <= 16; i++) {
			for(int j= 5; j <= us1[i]; j++) v.push_back(CP(SHUNZI, j, i, i + j - 1, 1));
			for(int j= 3; j <= us2[i]; j++) v.push_back(CP(SHUNZI, j * 2, i, i + j - 1, 2));
			for(int j= 2; j <= us3[i]; j++) v.push_back(CP(SHUNZI, j * 3, i, i + j - 1, 3));
			if(pai[i] < 3) continue;
			for(int j= 2; j <= 16; j++) {
				if(i == j || !pai[j]) continue;
				v.push_back(CP(SANDAI, 4, i, 1, j));
				if(pai[j] < 2) continue;
				v.push_back(CP(SANDAI, 5, i, 2, j));
			}
			if(pai[i] < 4) continue;
			for(int j= 2; j <= 16; j++) {
				if(i == j || !pai[j]) continue;
				for(int k= j + 1; k <= 16; k++) {
					if(i == k || !pai[k]) continue;
					v.push_back(CP(SIDAI, 6, i, 1, j, k));
					if(pai[j] < 2 || pai[k] < 2) continue;
					v.push_back(CP(SIDAI, 8, i, 2, j, k));
				}
				if(pai[j] == 4) v.push_back(CP(SIDAI, 8, i, 2, j, j));
				if(pai[j] > 2) v.push_back(CP(SIDAI, 6, i, 1, j, j));
			}
		}
		sort(v.begin(), v.end());
		dfs(n, 0, 0);
		cout << bestans << endl;
	}
	return 0;
}
/*
1 10
4 1
3 3
2 3
5 1
10 1
2 1
6 4
1 1
0 2
8 1
6
*/
/*
1 15
2 3
5 1
8 2
3 4
10 1
13 4
7 2
9 1
6 4
13 1
13 2
13 3
9 3
10 2
11 3
*/
/*
1 22
4 3
7 1
10 2
2 1
13 1
6 1
5 3
10 3
12 3
4 4
1 4
7 4
3 3
0 1
1 3
3 4
9 3
7 2
7 3
8 4
1 1
9 2
*/