#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <string.h>
#include <time.h>
#include <stdlib.h>
using namespace std;
int n, t, s, e, id[1005], idptr, tmpx, tmpy, tmpz;
struct MAT {
	int a[105][105];
	MAT operator+(const MAT &m2) const {
		MAT r;
		memset(&r, 0x3f, sizeof(r));
		for(int i= 1; i <= idptr; i++) {
			for(int j= 1; j <= idptr; j++) {
				for(int k= 1; k <= idptr; k++) {
					r.a[i][k]= min(r.a[i][k], a[i][j] + m2.a[j][k]);
				}
			}
		}
		return r;
	}
} base, res;
void qmin() {
	res= base, --n;
	while(n) {
		if(n & 1) res= res + base;
		base= base + base, n>>= 1;
	}
	return;
}

int main() {
	srand(time(0));
	memset(&base, 0x3f, sizeof(base));
	cin >> n >> t >> s >> e;
	for(int i= 1; i <= t; i++) {
		cin >> tmpz >> tmpx >> tmpy;
		if(!id[tmpx]) id[tmpx]= ++idptr;
		if(!id[tmpy]) id[tmpy]= ++idptr;
		base.a[id[tmpx]][id[tmpy]]= base.a[id[tmpy]][id[tmpx]]= tmpz;
	}
	qmin();
	cout << res.a[id[s]][id[e]] << endl;
	return 0;
}