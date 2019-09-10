#include <iostream>
#include <stdio.h>
#include <algorithm>
#define int long long
using namespace std;
int tmpi, w, tmpx1, tmpy1, tmpx2, tmpy2, opcnt, ans;
struct OPT {
	int id, typ, x, y, c;
	bool operator<(const OPT &o2) const {
		return id < o2.id;
	}
	void operator()(int _id, int _typ, int _x, int _y, int _c) {
		id= _id, typ= _typ, x= _x, y= _y, c= _c;
		return;
	}
} a[500005], b[500005];
int bitr[2000005];
#define lowb(x) ((x) & -(x))
void update(int x, int c) {
	while(x <= 2000010) bitr[x]+= c, x+= lowb(x);
	return;
}
void query(int x, int &res) {
	while(x) res+= bitr[x], x-= lowb(x);
	return;
}
void CDQ(int l, int r) {
	if(l == r) return;
	int mid= (l + r) >> 1;
	CDQ(l, mid), CDQ(mid + 1, r);
	int ml= l, mm= mid + 1, p= l;
	while(ml <= mid && mm <= r) {
		if(a[ml].x <= a[mm].x) {
			if(!a[ml].typ) update(a[ml].y, a[ml].c);
			b[p++]= a[ml++];
		}
		else {
			if(a[mm].typ) query(a[mm].y, a[mm].c);
			b[p++]= a[mm++];
		}
	}
	while(ml <= mid) {
		if(!a[ml].typ) update(a[ml].y, a[ml].c);
		b[p++]= a[ml++];
	}
	while(mm <= r) {
		if(a[mm].typ) query(a[mm].y, a[mm].c);
		b[p++]= a[mm++];
	}
	for(int i= l; i <= mid; i++)
		if(!a[i].typ) update(a[i].y, -a[i].c);
	for(int i= l; i <= r; i++) a[i]= b[i];
	return;
}
signed main() {
	cin >> tmpi >> w, ++w;
	while(cin >> tmpi) {
		if(tmpi == 1)
			cin >> tmpx1 >> tmpy1 >> tmpx2, a[++opcnt](opcnt, 0, tmpx1 + 1, tmpy1 + 1, tmpx2);
		else if(tmpi == 2)
			cin >> tmpx1 >> tmpy1 >> tmpx2 >> tmpy2, a[++opcnt](opcnt, 1, tmpx2 + 1, tmpy2 + 1, 0), a[++opcnt](opcnt, 1, tmpx1, tmpy2 + 1, 0), a[++opcnt](opcnt, 1, tmpx2 + 1, tmpy1, 0), a[++opcnt](opcnt, 1, tmpx1, tmpy1, 0);
		else
			break;
	}
	CDQ(1, opcnt);
	sort(a + 1, a + opcnt + 1);
	for(int i= 1; i <= opcnt; i++)
		if(a[i].typ) cout << a[i].c - a[i + 1].c - a[i + 2].c + a[i + 3].c << endl, i+= 3;
	return 0;
}
