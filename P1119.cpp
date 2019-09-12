#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
int n, m, q, tmpx, tmpy, tmpz, dis[205][205], lastq, f[205];
vector< int > w[100005];
int main() {
	cin >> n >> m;
	memset(dis, 0x3f, sizeof(dis));
	for(int i= 1; i <= n; i++) {
		cin >> tmpx, dis[i][i]= 0;
		w[tmpx].push_back(i);
	}
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz, ++tmpx, ++tmpy;
		dis[tmpx][tmpy]= dis[tmpy][tmpx]= min(dis[tmpx][tmpy], tmpz);
	}
	cin >> q;
	for(int i= 1; i <= q; i++) {
		cin >> tmpx >> tmpy >> tmpz, ++tmpx, ++tmpy;
		for(; lastq <= tmpz; lastq++) {
			for(int k= 0, nown; k < w[lastq].size(); k++) {
				nown= w[lastq][k], f[nown]= 1;
				for(int l1= 1; l1 <= n; l1++)
					for(int l2= 1; l2 <= n; l2++) dis[l1][l2]= min(dis[l1][l2], dis[l1][nown] + dis[nown][l2]);
			}
		}
		cout << (dis[tmpx][tmpy] == 0x3f3f3f3f || !f[tmpx] || !f[tmpy] ? -1 : dis[tmpx][tmpy]) << endl;
	}
	return 0;
}