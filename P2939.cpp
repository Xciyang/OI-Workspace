#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
int n, m, k, head[230000], edptr= 1, tmpx, tmpy, tmpz;
struct edge {
	int to, nexty, dis;
} eds[4600000];
inline int read() {
	int e= 0, f= 1;
	char ch= getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') e= e * 10 + ch - '0', ch= getchar();
	return e * f;
}
void add(int a, int b, int c) {
	eds[edptr].to= b, eds[edptr].nexty= head[a], eds[edptr].dis= c;
	head[a]= edptr++;
	return;
}
int dis[230000], nown, to, walkpast[230000];
priority_queue< pair< int, int > > qu;
void dij() {
	memset(dis, 0x3f, sizeof(dis));
	memset(walkpast, 0, sizeof(walkpast));
	dis[1]= 0, qu.push(make_pair(0, 1));
	while(!qu.empty()) {
		nown= qu.top().second, qu.pop();
		if(walkpast[nown]) continue;
		walkpast[nown]= 1;
		for(int i= head[nown]; i; i= eds[i].nexty) {
			to= eds[i].to;
			if(dis[to] > dis[nown] + eds[i].dis) {
				dis[to]= dis[nown] + eds[i].dis;
				qu.push(make_pair(-dis[to], to));
			}
		}
	}
	return;
}
int main() {
	n= read(), m= read(), k= read();
	for(int i= 0; i < m; i++) {
		tmpx= read(), tmpy= read(), tmpz= read();
		add(tmpx, tmpy, tmpz), add(tmpy, tmpx, tmpz);
		for(int j= 1; j <= k; j++) {
			add((j - 1) * n + tmpx, j * n + tmpy, 0), add((j - 1) * n + tmpy, j * n + tmpx, 0);
			add(j * n + tmpx, j * n + tmpy, tmpz), add(j * n + tmpy, j * n + tmpx, tmpz);
		}
	}
	dij();
	cout << dis[k * n + n] << endl;
	return 0;
}