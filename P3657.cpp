#include <iostream>
#include <stdio.h>
using namespace std;
int n;
int a[1000005], b[1000005], c[1000005];
int v[1000005], f[1000005];
inline int lowb(int x) {
	return x & -x;
}
inline void update(int x, int c) {
	for(; x <= n + 1; x+= lowb(x)) v[x]= max(v[x], c);
	return;
}
inline int query(int x) {
	int res= 0;
	for(; x; x-= lowb(x)) res= max(res, v[x]);
	return res;
}
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i];
	for(int i= 1; i <= n; i++) cin >> b[i], c[b[i]]= i;
	for(int i= 1; i <= n; i++) {
		for(int j= max(1, a[i] - 4); j <= min(n, a[i] + 4); j++) {
			f[j]= query(c[j]);
		}
		for(int j= max(1, a[i] - 4); j <= min(n, a[i] + 4); j++) {
			update(c[j] + 1, f[j] + 1);
		}
	}
	cout << query(n + 1) << endl;
	return 0;
}