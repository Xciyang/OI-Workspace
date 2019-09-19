#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int n, m, s, tmpx, tmpy, tmpz, tmpk, tmpu, tmpv, f[50005];
struct EDGE {
	int typ, tl, tr;
};
vector< EDGE > edg[50005];
inline int getf(int x) {
	return f[x] == x ? x : f[x]= getf(f[x]);
}
int main() {
	cin >> n >> m >> s;
	for(int i= 1; i <= n; i++) f[i]= i;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx;
		if(tmpx == 1) {
		}
		else {
		}
	}
	return 0;
}