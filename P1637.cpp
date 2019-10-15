#include <iostream>
#include <stdio.h>
#include <map>
#include <string.h>
#include <algorithm>
using namespace std;
int n, a[30005], id[30005], idptr, b[30005], l[30005], r[30005];
map< int, int > mm;
int v[100005];
long long ans;
inline int lowb(int x) {
	return x & -x;
}
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
	for(int i= 1; i <= n; i++) cin >> a[i], b[i]= a[i];
	sort(b + 1, b + n + 1);
	idptr= unique(b + 1, b + n + 1) - b - 1;
	for(int i= 1; i <= idptr; i++) mm[b[i]]= i;
	for(int i= 1; i <= n; i++) {
		l[i]= query(mm[a[i]] - 1);
		update(mm[a[i]], 1);
	}
	memset(v, 0, sizeof(v));
	for(int i= n; i; i--) {
		r[i]= query(idptr) - query(mm[a[i]]);
		update(mm[a[i]], 1);
	}
	for(int i= 1; i <= n; i++) ans+= 1LL * l[i] * r[i];
	cout << ans << endl;
	return 0;
}