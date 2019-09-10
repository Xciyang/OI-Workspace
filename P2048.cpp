#include <iostream>
#include <stdio.h>
#include <queue>
#include <math.h>
#define int long long
using namespace std;
int n, k, L, R, a[500005], suma[500005], ans;
int stmax[500005][25], maxid[500005][25];
void stinit() {
	for(int i= 1; i <= n; i++) maxid[i][0]= i;
	for(int j= 1; (1 << j) <= n; j++)
		for(int i= 1; i + (1 << j) - 1 <= n; i++) maxid[i][j]= (suma[maxid[i][j - 1]] > suma[maxid[i + (1 << (j - 1))][j - 1]] ? maxid[i][j - 1] : maxid[i + (1 << (j - 1))][j - 1]);
	return;
}
int getmax(int l, int r) {
	int j= log2(r - l + 1);
	return suma[maxid[l][j]] > suma[maxid[r - (1 << j) + 1][j]] ? maxid[l][j] : maxid[r - (1 << j) + 1][j];
}
struct NODE {
	int l, r, id, nown;
	bool operator<(const NODE &n2) const {
		return suma[nown] - suma[id - 1] < suma[n2.nown] - suma[n2.id - 1];
	}
} tmpn, tmpn2;
priority_queue< NODE > qu;
signed main() {
	cin >> n >> k >> L >> R;
	for(int i= 1; i <= n; i++) cin >> a[i], suma[i]= suma[i - 1] + a[i];
	stinit();
	for(int i= 1; i + L - 1 <= n; i++) {
		tmpn.id= i, tmpn.l= i + L - 1, tmpn.r= min(n, i + R - 1);
		tmpn.nown= getmax(tmpn.l, tmpn.r);
		qu.push(tmpn);
	}
	for(int i= 0; i < k; i++) {
		tmpn= qu.top(), qu.pop();
		ans+= suma[tmpn.nown] - suma[tmpn.id - 1];
		tmpn2.id= tmpn.id;
		if(tmpn.nown != tmpn.l) {
			tmpn2.l= tmpn.l, tmpn2.r= tmpn.nown - 1;
			tmpn2.nown= getmax(tmpn2.l, tmpn2.r);
			qu.push(tmpn2);
		}
		if(tmpn.nown != tmpn.r) {
			tmpn2.l= tmpn.nown + 1, tmpn2.r= tmpn.r;
			tmpn2.nown= getmax(tmpn2.l, tmpn2.r);
			qu.push(tmpn2);
		}
	}
	cout << ans << endl;
	return 0;
}