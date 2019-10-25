#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int T, n, m, tmpx, tmpy, tmpz, tmpk;
struct EDGE {
	int to;
	double dis;
};
vector< EDGE > v[1005];
int wp[1005];
double jl[1005];
inline double absd(double x) {
	return x < 0 ? -x : x;
}
inline int isZero(double x) {
	return absd(x) < 1e-5;
}
int dfs(int nown, double d) {
	wp[nown]= 1, jl[nown]= d;
	for(int i= 0, to; i < (int)v[nown].size(); i++) {
		to= v[nown][i].to;
		if(!wp[to] && dfs(to, d * v[nown][i].dis)) return 1;
		if(!isZero(d * v[nown][i].dis - jl[to])) return 1;
	}
	return 0;
}
int main() {
	cin >> T;
	for(int i= 1; i <= T; i++) {
		cin >> n >> m;
		for(int i= 1; i <= n; i++) v[i].clear(), wp[i]= 0;
		for(int i= 1; i <= m; i++) {
			cin >> tmpx >> tmpy >> tmpz >> tmpk;
			v[tmpx].push_back(EDGE{tmpy, (double)tmpk / tmpz});
			v[tmpy].push_back(EDGE{tmpx, (double)tmpz / tmpk});
		}
		int flag= 0;
		for(int i= 1; i <= n; i++) 
			if(!wp[i]) flag+= dfs(i, 1);
		cout << "Case #" << i << ": ";
		if(!flag)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	return 0;
}