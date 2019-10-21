#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;
int n, m, num[300005];
int a[100005][4], v[1200005][4], f[100005][4];
map< int, int > mm;
void update(int id, int nown, int l, int r, int mlr, int c) {
	if(l == r) {
		v[nown][id]= max(v[nown][id], c);
		return;
	}
	int mid= (l + r) >> 1;
	if(mid >= mlr)
		update(id, nown << 1, l, mid, mlr, c);
	else
		update(id, nown << 1 | 1, mid + 1, r, mlr, c);
	v[nown][id]= max(v[nown << 1][id], v[nown << 1 | 1][id]);
	return;
}
int query(int id, int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) return v[nown][id];
	int mid= (l + r) >> 1, res= 0;
	if(mid >= ml) res= max(res, query(id, nown << 1, l, mid, ml, mr));
	if(mid < mr) res= max(res, query(id, nown << 1 | 1, mid + 1, r, ml, mr));
	return res;
}
int main() {
	cin >> n;
	for(int j= 1; j <= 3; j++)
		for(int i= 1; i <= n; i++) cin >> a[i][j], num[++num[0]]= a[i][j];
	sort(num + 1, num + num[0] + 1);
	m= unique(num + 1, num + num[0] + 1) - num - 1;
	for(int i= 1; i <= m; i++) mm[num[i]]= i;
	for(int i= 1; i <= n; i++) {
		f[i][0]= max(f[i][0], query(0, 1, 1, m, 1, mm[a[i][1]]));
		f[i][0]= max(f[i][0], query(1, 1, 1, m, 1, mm[a[i][1]]));
		f[i][0]= max(f[i][0], query(2, 1, 1, m, 1, mm[a[i][1]]));
		f[i][0]= max(f[i][0], query(3, 1, 1, m, 1, mm[a[i][1]]));
		f[i][1]= max(f[i][1], query(0, 1, 1, m, mm[a[i][2]], m));
		f[i][1]= max(f[i][1], query(1, 1, 1, m, mm[a[i][2]], m));
		f[i][1]= max(f[i][1], query(2, 1, 1, m, mm[a[i][2]], m));
		f[i][1]= max(f[i][1], query(3, 1, 1, m, mm[a[i][2]], m));
		f[i][2]= max(f[i][2], query(0, 1, 1, m, 1, mm[a[i][3]]));
		f[i][2]= max(f[i][2], query(1, 1, 1, m, 1, mm[a[i][3]]));
		f[i][2]= max(f[i][2], query(2, 1, 1, m, 1, mm[a[i][3]]));
		f[i][3]= max(f[i][3], query(0, 1, 1, m, mm[a[i][3]], m));
		f[i][3]= max(f[i][3], query(1, 1, 1, m, mm[a[i][3]], m));
		f[i][3]= max(f[i][3], query(3, 1, 1, m, mm[a[i][3]], m));
		update(0, 1, 1, m, mm[a[i][1]], f[i][0] + 1);
		update(1, 1, 1, m, mm[a[i][2]], f[i][1] + 1);
		update(2, 1, 1, m, mm[a[i][3]], f[i][2] + 1);
		update(3, 1, 1, m, mm[a[i][3]], f[i][3] + 1);
	}
	cout << max(max(query(0, 1, 1, m, 1, m), query(1, 1, 1, m, 1, m)), max(query(2, 1, 1, m, 1, m), query(3, 1, 1, m, 1, m))) << endl;
	return 0;
}