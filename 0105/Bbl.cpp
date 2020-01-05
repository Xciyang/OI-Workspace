#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <queue>
using namespace std;
int n, a[3005], dis[3005][3005], ans = 0;
void BFS(int x) {
	queue< int > qu;
	for(int i = 1; i <= n; i++) dis[x][i] = 0;
	qu.push(x), dis[x][x] = 1;
	register int nown;
	while(!qu.empty()) {
		nown = qu.front(), qu.pop();
		for(register int i = max(-a[nown], 1 - nown); i <= min(a[nown], n - nown); i++) {
			if(!dis[x][nown + i]) {
				dis[x][nown + i] = dis[x][nown] + 1;
				qu.push(nown + i);
			}
		}
	}
	for(int i = 1; i <= n; i++) --dis[x][i];
	return;
}
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) BFS(i);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) ans = max(ans, min(dis[i][j], dis[j][i]));
	cout << ans << endl;
	return 0;
}
