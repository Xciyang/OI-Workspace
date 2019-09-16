#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
int n, m, tmpx, tmpy, tmpz, head[1505], edptr= 1;
struct edge {
	int to, dis, nexty;
} eds[50005];
void add(int a, int b, int c) {
	eds[edptr].to= b, eds[edptr].nexty= head[a], eds[edptr].dis= c;
	head[a]= edptr++;
	return;
}
queue< int > qu;
int wp[1505], dis[1505];
int main() {
	cin >> n >> m;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		add(tmpx, tmpy, tmpz);
	}
	dis[1]= 0, wp[1]= 1, qu.push(1);
	register int nown;
	while(!qu.empty()) {
		nown= qu.front(), qu.pop();
		wp[nown]= 0;
		for(int i= head[nown], to; i; i= eds[i].nexty) {
			to= eds[i].to;
			if(dis[to] < dis[nown] + eds[i].dis) {
				dis[to]= dis[nown] + eds[i].dis;
				if(!wp[to]) wp[to]= 1, qu.push(to);
			}
		}
	}
	cout << (dis[n] ? dis[n] : -1) << endl;
	return 0;
}