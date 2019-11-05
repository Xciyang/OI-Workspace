#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
int n, m, tmpx, tmpy, tmpz;
long long dis[105][105], siz[105][105];
double ans[105];
int main() {
	cin >> n >> m;
	memset(dis, 0x3f, sizeof(dis));
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		dis[tmpx][tmpy]= dis[tmpy][tmpx]= tmpz;
		siz[tmpx][tmpy]= siz[tmpy][tmpx]= 1;
	}
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= n; j++) {
			for(int k= 1; k <= n; k++) {
				if(dis[j][i] + dis[i][k] == dis[j][k]) {
					siz[j][k]+= siz[j][i] * siz[i][k];
				}
				if(dis[j][i] + dis[i][k] < dis[j][k]) {
					dis[j][k]= dis[j][i] + dis[i][k];
					siz[j][k]= siz[j][i] * siz[i][k];
				}
			}
		}
	}
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= n; j++) {
			for(int k= 1; k <= n; k++) {
				if(i == j || i == k || j == k) continue;
				if(dis[j][i] + dis[i][k] == dis[j][k]) {
					ans[i]+= 1.0 * siz[j][i] * siz[i][k] / siz[j][k];
				}
			}
		}
	}
	for(int i= 1; i <= n; i++) {
		printf("%.3lf\n", ans[i]);
	}
	return 0;
}