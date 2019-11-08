#include <iostream>
#include <stdio.h>
using namespace std;
int p, f[100005], siz[100005], tmpx, tmpy, d[100005];
inline int getf(int x) {
	if(f[x] == x) return x;
	int res= getf(f[x]);
	d[x]+= d[f[x]];
	return f[x]= res;
}
char tmpc;
int main() {
	for(int i= 1; i <= 100000; i++) f[i]= i, siz[i]= 1;
	cin >> p;
	for(int i= 1; i <= p; i++) {
		cin >> tmpc >> tmpx;
		if(tmpc == 'C') {
			getf(tmpx);
			cout << d[tmpx] << endl;
		}
		else {
			cin >> tmpy;
			int fx= getf(tmpx), fy= getf(tmpy);
			f[fx]= fy, d[fx]= siz[fy], siz[fy]+= siz[fx];
		}
	}
	return 0;
}