#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, v[100005], f[100005], l[100005], r[100005], d[100005];
int tmpx, tmpy;
inline int getf(int x) {
	return f[x] == x ? x : f[x]= getf(f[x]);
}
int merge(int x, int y) {
	if(!x || !y) return x + y;
	if(v[x] < v[y]) swap(x, y);
	r[x]= merge(r[x], y), f[l[x]]= f[r[x]]= f[x]= x;
	if(d[r[x]] > d[l[x]]) swap(r[x], l[x]);
	d[x]= d[r[x]] + 1;
	return x;
}
int solve(int x, int y) {
	x= getf(x), y= getf(y);
	if(x == y) return -1;
	v[x]>>= 1, v[y]>>= 1;
	int newx= merge(l[x], r[x]), newy= merge(l[y], r[y]);
	l[x]= r[x]= l[y]= r[y]= d[x]= d[y]= 0;
	newx= merge(newx, x), newy= merge(newy, y), newx= merge(newx, newy);
	return v[newx];
}
int main() {
	while(cin >> n) {
		for(int i= 1; i <= n; i++) cin >> v[i], f[i]= i, l[i]= r[i]= d[i]= 0;
		cin >> m;
		for(int i= 1; i <= m; i++) {
			cin >> tmpx >> tmpy;
			cout << solve(tmpx, tmpy) << endl;
		}
	}
	return 0;
}