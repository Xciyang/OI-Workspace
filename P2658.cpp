#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
int m, n, ans, h[505][505], lx1, ly1, cnt, maxs, c[505][505];
int walkpast[505][505], moves[4][2]= {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
inline int abs(int x) {
	return x < 0 ? -x : x;
}
int judge(int d) {
	memset(walkpast, 0, sizeof(walkpast));
	queue< int > qx, qy;
	qx.push(lx1), qy.push(ly1), walkpast[lx1][ly1]= 1;
	register int nowx, nowy, newx, newy, res= 1;
	while(!qx.empty()) {
		nowx= qx.front(), nowy= qy.front(), qx.pop(), qy.pop();
		for(int i= 0; i < 4; i++) {
			newx= nowx + moves[i][0], newy= nowy + moves[i][1];
			if(newx < 1 || newx > n || newy < 1 || newy > m || walkpast[newx][newy] || abs(h[newx][newy] - h[nowx][nowy]) > d) continue;
			if(c[newx][newy])
				if(++res == cnt) return 1;
			walkpast[newx][newy]= 1, qx.push(newx), qy.push(newy);
		}
	}
	return 0;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i= 1; i <= n; i++)
		for(int j= 1; j <= m; j++) scanf("%d", &h[i][j]), maxs= max(maxs, h[i][j]);
	for(int i= 1; i <= n; i++)
		for(int j= 1; j <= m; j++) {
			scanf("%d", &c[i][j]);
			if(c[i][j]) ++cnt, lx1= i, ly1= j;
		}
	if(cnt == 1 || cnt == 0) {
		printf("0\n");
		return 0;
	}
	int l= 0, r= maxs, mid;
	while(l <= r) {
		mid= (l + r) >> 1;
		if(judge(mid))
			r= mid - 1, ans= mid;
		else
			l= mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}