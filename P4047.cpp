#include <iostream>
#include <stdio.h>
#include <queue>
#include <math.h>
#include <algorithm>
using namespace std;
int n, m, posx[1005], posy[1005], vis[1005];
double dis[1005];
priority_queue< pair< double, int > > qu;
double getd(int i, int j) {
	return sqrt((posx[i] - posx[j]) * (posx[i] - posx[j]) + (posy[i] - posy[j]) * (posy[i] - posy[j]));
}
void prim() {
	vis[1]= 1;
	for(int i= 2; i <= n; i++) qu.push(make_pair(-getd(1, i), i));
	for(int i= 1, nown; i < n; i++) {
		while(!qu.empty() && vis[qu.top().second]) qu.pop();
		dis[i]= -qu.top().first, nown= qu.top().second, vis[nown]= 1;
		for(int i= 1; i <= n; i++)
			if(!vis[i]) qu.push(make_pair(-getd(nown, i), i));
	}
	return;
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) cin >> posx[i] >> posy[i];
	prim();
	sort(dis + 1, dis + n);
	printf("%.2lf\n", dis[n - m + 1]);
	return 0;
}