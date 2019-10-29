#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, w[300005], t[300005], ans[300005], fid[300005];
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
		// for(int i= 0; i < n; i++) ans[i]= a[t[i]].id;
		for(int i= 0; i < n; i++) ans[i]= t[i];
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
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i].x >> a[i].y, a[i].id= i;
	sort(a + 1, a + n + 1);
	for(int i= 1; i <= n; i++) cout << a[i].id << ' ';
	cout << endl;
	return 0;
}
/*
3
1 2
4 4
3 1
*/