#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>
#include <algorithm>
using namespace std;
int n, h[100005], id[100005], nh[100005], idptr, l[100005], r[100005];
int ans;
map< int, int > mm;
inline int lowb(int x) {
	return x & -x;
}
int v[100005];
inline int query(int x) {
	int res= 0;
	for(; x; x-= lowb(x)) res+= v[x];
	return res;
}
inline void update(int x, int c) {
	for(; x <= idptr; x+= lowb(x)) v[x]+= c;
	return;
}
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> h[i], nh[i]= h[i];
	sort(nh + 1, nh + n + 1);
	idptr= unique(nh + 1, nh + n + 1) - nh - 1;
	for(int i= 1; i <= idptr; i++) mm[nh[i]]= i;
	for(int i= 1; i <= n; i++) {
		l[i]= query(idptr) - query(mm[h[i]]);
		update(mm[h[i]], 1);
	}
	memset(v, 0, sizeof(v));
	for(int i= n; i; i--) {
		r[i]= query(idptr) - query(mm[h[i]]);
		update(mm[h[i]], 1);
	}
	for(int i= 1; i <= n; i++) {
		if(l[i] < r[i]) swap(l[i], r[i]);
		if(l[i] > r[i] * 2) ++ans;
	}
	cout << ans << endl;
	return 0;
}