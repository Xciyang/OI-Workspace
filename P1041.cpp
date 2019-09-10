#include <iostream>
#include <stdio.h>
using namespace std;
int n, p, f[301], head[301], edptr= 1;
int tmpx, tmpy;
struct edge {
	int to, nexty;
} eds[1001];
void add(int a, int b) {
	eds[edptr].to= b, eds[edptr].nexty= head[a];
	head[a]= edptr++;
	return;
}
void dp(int nown, int fa) {
	int sons= 0, maxs= 0, tot= 0;
	for(int i= head[nown], to; i; i= eds[i].nexty) {
		to= eds[i].to;
		if(to == fa) continue;
		dp(to, nown);
		++sons, maxs= max(maxs, f[to]), tot+= f[to];
	}
	if(sons >= 2) f[nown]= tot - maxs + sons - 1;
	return;
}
int main() {
	cin >> n >> p;
	for(int i= 0; i < p; i++) {
		cin >> tmpx >> tmpy;
		add(tmpx, tmpy), add(tmpy, tmpx);
	}
	dp(1, -1);
	cout << f[1] + 1 << endl;
	return 0;
}
/*
13 12
1 2
1 3
1 4
1 5
1 6
6 7
6 8
6 9
2 10
3 11
4 12
5 13
*/