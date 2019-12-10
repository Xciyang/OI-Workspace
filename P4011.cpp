#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
int n, m, p, k, s, tmpx1, tmpy1, tmpx2, tmpy2;
int g[11][11][11][11], v[11][11];
struct NODE {
	int x, y, step, s;
};
int wp[11][11][1 << 16];
int moves[][2]= {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
int main() {
	cin >> n >> m >> p >> k;
	for(int i= 1; i <= k; i++) {
		cin >> tmpx1 >> tmpy1 >> tmpx2 >> tmpy2;
		cin >> g[tmpx1][tmpy1][tmpx2][tmpy2];
		if(!g[tmpx1][tmpy1][tmpx2][tmpy2]) g[tmpx1][tmpy1][tmpx2][tmpy2]= 13;
		g[tmpx2][tmpy2][tmpx1][tmpy1]= g[tmpx1][tmpy1][tmpx2][tmpy2];
	}
	cin >> s;
	for(int i= 1; i <= s; i++) {
		cin >> tmpx1 >> tmpy1 >> tmpx2;
		v[tmpx1][tmpy1]|= (1 << tmpx2);
	}
	queue< NODE > qu;
	register NODE nown, to;
	qu.push(NODE{1, 1, 0, v[1][1]});
	wp[1][1][v[1][1]]= 1;
	while(!qu.empty()) {
		nown= qu.front(), qu.pop();
		if(nown.x == n && nown.y == m) {
			cout << nown.step << endl;
			return 0;
		}
		to.step = nown.step + 1;
		for(int i= 0; i < 4; i++) {
			to.x= nown.x + moves[i][0], to.y= nown.y + moves[i][1];
			if(to.x < 1 || to.x > n || to.y < 1 || to.y > m || (g[nown.x][nown.y][to.x][to.y] && (nown.s & (1 << g[nown.x][nown.y][to.x][to.y])) == 0)) continue;
			to.s= (nown.s | v[to.x][to.y]);
			if(wp[to.x][to.y][to.s]) continue;
			qu.push(to);
			wp[to.x][to.y][to.s]= 1;
		}
	}
	cout << -1 << endl;
	return 0;
}