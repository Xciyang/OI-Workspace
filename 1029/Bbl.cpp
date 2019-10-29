#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, w[300005], t[300005], ans[300005], ans2[300005], fid[300005];
struct NODE {
	long long x, y;
	int id;
	inline int operator<(const NODE &n2) const {
		return x * x + y * y < n2.x * n2.x + n2.y * n2.y;
	}
} a[300005], tmpn;
long long bestans= 4e9;
inline long long getSum(const NODE &n2) {
	return n2.x * 2 + n2.y * 2;
}
void dfs(int finish, long long sum, long long nowans) {
	if(nowans >= bestans) return;
	if(finish == n) {
		for(int i= 0; i < n; i++) ans2[i]= a[t[i]].id;
#ifdef TEST
		for(int i= 0; i < n; i++) ans[i]= t[i];
#endif
		bestans= nowans;
		return;
	}
	NODE lst= tmpn;
	for(int i= 1; i <= n; i++) {
		if(w[i]) continue;
		tmpn.x= max(tmpn.x, a[i].x), tmpn.y= max(tmpn.y, a[i].y);
		long long newsum= getSum(tmpn);
		t[finish]= i, w[i]= 1;
		dfs(finish + 1, newsum, max(nowans, newsum - sum));
		tmpn= lst, w[i]= 0;
	}
	return;
}
int main() {
	// freopen("./1.out", "w", stdout);
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i].x >> a[i].y, a[i].id= i;
	sort(a + 1, a + n + 1);
	tmpn.x= tmpn.y= 1;
	dfs(0, 4, 0);
#ifdef TEST
	for(int i= 0; i < n; i++) cout << ans[i] << ' ';
	cout << endl;
#endif
	for(int i= 0; i < n; i++) cout << ans2[i] << ' ';
	cout << endl;
	return 0;
}
/*
3
1 2
4 4
3 1
*/
/*
6
17 15
6 10
7 3
16 15
19 10
2 15

3 2 6 4 5 1
*/
/*
10
959568429 51131434
863988214 971350931
647974012 815718751
122459540 874488203
724622011 440070095
483570619 527502788
721942633 115200086
409306085 80405903
353190835 39433964
670879676 908368093

*/