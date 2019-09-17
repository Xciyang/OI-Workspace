#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int n, m, r, e[1004], ks[1004], js[1004];
int F[2000006][2];
vector< int > b[2000006];
int main() {
	cin >> n >> m >> r;
	for(int i= 1; i <= m; i++) cin >> ks[i] >> js[i] >> e[i], b[js[i]].push_back(i);
	for(int i= 1; i <= n + r; i++) {
		F[i][0]= F[i - 1][0];
		if(i >= r) F[i][0]= max(F[i][0], F[i - r][1]);
		F[i][1]= F[i - 1][1];
		for(int j= 0; j < b[i].size(); j++) F[i][1]= max(F[i][1], F[ks[b[i][j]]][0] + e[b[i][j]]);
	}
	cout << F[n + r][0] << endl;
	return 0;
}