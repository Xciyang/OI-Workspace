#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int n, k[505], stepmax;
vector< double > p[505];
struct NODE {
	int id;
	double tot;
	inline int operator<(const NODE &n2) const {
		return tot < n2.tot;
	}
} a[505];
double tmpx, ans;
void dfs(int nowx, int nowy, int step, double g) {
	if(nowx == n + 1 || nowy == p[a[nowx].id].size()) {
		ans+= step * g;
		return;
	}
	dfs(nowx, nowy + 1, step + 1, g * (1 - p[a[nowx].id][nowy]));
	dfs(nowx + 1, 0, step + 1, g * p[a[nowx].id][nowy]);
	return;
}
double w[2][505][505 * 505];
void DP() {
	for(int i= 1, ch, reali, realj; i <= n; i++) {
		ch= i & 1, reali= a[i].id, realj= a[i - 1].id;
		stepmax+= p[reali].size();
		for(int k= 1; k <= stepmax; k++) w[ch][0][k]= 0;
		if(i == 1) {
			w[ch][0][0]= 1;
		}
		else {
			for(int j= 0; j < p[realj].size(); j++) {
				for(int k= 1; k <= stepmax; k++) w[ch][0][k]+= w[ch ^ 1][j][k - 1] * p[realj][j];
			}
		}
		for(int j= 0; j < p[reali].size(); j++) {
			for(int k= 1; k <= stepmax; k++) w[ch][j + 1][k]= 0;
			for(int k= 1; k <= stepmax; k++) w[ch][j + 1][k]+= w[ch][j][k - 1] * (1 - p[reali][j]);
		}
		for(int k= 1; k <= n; k++) {
			ans+= w[ch][p[reali].size()][k] * k;
		}
	}
	return;
}
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) {
		cin >> k[i];
		a[i].id= i, a[i].tot= 1;
		for(int j= 1; j <= k[i]; j++) {
			cin >> tmpx;
			p[i].push_back(tmpx);
			a[i].tot*= tmpx;
		}
	}
	sort(a + 1, a + n + 1);
	// dfs(1, 0, 0, 1);
	DP();
	printf("%.9lf\n", ans);
	return 0;
}
/*
2
3 0.1 0.1 0.1
2 0.9 0.9
*/