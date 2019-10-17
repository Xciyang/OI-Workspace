#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
int m, f[100005], n, tmpx, typ[100005];
vector< int > v[100005];
void DP(int nown) {
	if(v[nown].empty()) {
		f[nown]= 1;
		return;
	}
	int res1= 0, res2= 0, res3= 0, res4= 0;
	for(int i= 0, to; i < v[nown].size(); i++) {
		to= v[nown][i];
		DP(to);
		if(f[to] & 1) {
			res1= 1;
			if(res2) {
				f[nown]= 4;
				return;
			}
		}
		if(f[to] & 2) {
			res2= 1;
			if(res1) {
				f[nown]= 4;
				return;
			}
		}
		if(!(f[to] ^ 8)) {
			f[nown]= 4;
			return;
		}
		if(f[to] & 4) {
            f[nown]|= 8;

		}
		if(f[to] & 8) {
		}
	}
	return;
}
int main() {
	cin >> m;
	if(m == 1) {
		cin >> n;
		v[1].clear();
		for(int i= 2; i <= n; i++) {
			cin >> tmpx;
			v[tmpx].push_back(i), v[i].clear();
		}
        DP(1);
	}
	return 0;
}