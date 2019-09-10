#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m, v, e, tmpx, tmpy, tmpz;
int c[2005], d[2005], dis[305][305];
double k[2005], f[2005][2005][2];
int main() {
	scanf("%d%d%d%d", &n, &m, &v, &e);
	memset(dis, 0x3f, sizeof(dis));
	for(int i= 1; i <= n; i++) scanf("%d", c + i);
	for(int i= 1; i <= n; i++) scanf("%d", d + i);
	for(int i= 1; i <= n; i++) scanf("%lf", k + i);
	for(int i= 1; i <= e; i++) {
		scanf("%d%d%d", &tmpx, &tmpy, &tmpz);
		dis[tmpx][tmpy]= dis[tmpy][tmpx]= min(dis[tmpy][tmpx], tmpz);
	}
	for(int i= 1; i <= v; i++)
		for(int j= 1; j <= v; j++)
			for(int k= 1; k <= v; k++) dis[j][k]= min(dis[j][k], dis[j][i] + dis[i][k]);
	for(int i= 1; i <= v; i++) dis[0][i]= dis[i][0]= dis[i][i]= 0;
	for(int i= 0; i <= n; i++)
		for(int j= 0; j <= m; j++) f[i][j][0]= f[i][j][1]= 1e18;
	f[1][0][0]= f[1][1][1]= 0;
	for(int i= 2; i <= n; i++) {
		f[i][0][0]= f[i - 1][0][0] + dis[c[i]][c[i - 1]];
		for(int j= 1; j <= min(i, m); j++) {
			f[i][j][0]= min(f[i - 1][j][0] + dis[c[i]][c[i - 1]], f[i - 1][j][1] + (1 - k[i - 1]) * dis[c[i]][c[i - 1]] + k[i - 1] * dis[c[i]][d[i - 1]]);
			f[i][j][1]= min(f[i - 1][j - 1][0] + (1 - k[i]) * dis[c[i]][c[i - 1]] + k[i] * dis[d[i]][c[i - 1]],
							f[i - 1][j - 1][1] + k[i - 1] * k[i] * dis[d[i]][d[i - 1]] + k[i - 1] * (1 - k[i]) * dis[c[i]][d[i - 1]] + (1 - k[i - 1]) * k[i] * dis[d[i]][c[i - 1]] + (1 - k[i]) * (1 - k[i - 1]) * dis[c[i]][c[i - 1]]);
		}
	}
	double ans= 1e18;
	for(int i= 0; i <= m; i++) ans= min(ans, min(f[n][i][1], f[n][i][0]));
	printf("%.2lf\n", ans);
	return 0;
}