#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, tmpx, tmpy, tmpz, rot[100005], siz[100005], d[100005], l[100005], r[100005];
long long sum[100005], ans;
struct RZ {
	int b, c, l;
} rzs[100005];
int merge(int x, int y) {
	if(!x || !y) return x + y;
	if(rzs[x].c < rzs[y].c) swap(x, y);
	r[x]= merge(r[x], y);
	if(d[l[x]] < d[r[x]]) swap(l[x], r[x]);
	d[x]= d[r[x]] + 1;
	return x;
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) {
		cin >> rzs[i].b >> rzs[i].c >> rzs[i].l;
		ans= max(ans, (long long)rzs[i].l);
		siz[i]= 1, rot[i]= i, sum[i]= rzs[i].c;
	}
	for(int i= n, fa; i > 1; i--) {
		fa= rzs[i].b, rot[fa]= merge(rot[i], rot[fa]);
		siz[fa]+= siz[i], sum[fa]+= sum[i];
		while(sum[fa] > m) {
			sum[fa]-= rzs[rot[fa]].c, --siz[fa];
			rot[fa]= merge(l[rot[fa]], r[rot[fa]]);
		}
		ans= max(ans, (long long)rzs[fa].l * siz[fa]);
	}
	cout << ans << endl;
	return 0;
}