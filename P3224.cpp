#include <iostream>
#include <stdio.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using namespace std;
int n, m, q, f[100005], tmpx, tmpy;
char tmpt;
struct NODE {
	int id, imp;
	inline int operator<(const NODE &n2) const {
		return imp < n2.imp;
	}
};
tree< NODE, null_type, less< NODE >, rb_tree_tag, tree_order_statistics_node_update > nd[100005];

inline int getf(int x) {
	return f[x] == x ? x : (f[x]= getf(f[x]));
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) {
		cin >> tmpx;
		f[i]= i, nd[i].insert(NODE{i, tmpx});
	}
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy;
		tmpx= getf(tmpx), tmpy= getf(tmpy);
		if(tmpx == tmpy) continue;
		if(nd[tmpx].size() > nd[tmpy].size()) swap(tmpx, tmpy);
		f[tmpx]= tmpy;
		for(auto a : nd[tmpx]) nd[tmpy].insert(a);
	}
	cin >> q;
	for(int i= 1; i <= q; i++) {
		cin >> tmpt >> tmpx >> tmpy;
		if(tmpt == 'Q') {
			tmpx= getf(tmpx);
			if(tmpy > nd[tmpx].size())
				cout << -1 << endl;
			else
				cout << (*nd[tmpx].find_by_order(tmpy - 1)).id << endl;
		}
		else {
			tmpx= getf(tmpx), tmpy= getf(tmpy);
			if(tmpx == tmpy) continue;
			if(nd[tmpx].size() > nd[tmpy].size()) swap(tmpx, tmpy);
			f[tmpx]= tmpy;
			for(auto a : nd[tmpx]) nd[tmpy].insert(a);
		}
	}
	return 0;
}