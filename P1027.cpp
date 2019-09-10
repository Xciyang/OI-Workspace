#include <iostream>
#include <stdio.h>
#include <math.h>
#include <queue>
using namespace std;
int n, s, t, A, B;
double nx[500], ny[500], dis[500], T[200], ans;
inline int home(int x, int y) {
	return x / 4 == y / 4;
}
inline double epow2(double x1, double y1, double x2, double y2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
inline double getd(int x, int y) {
	return sqrt(epow2(nx[x], ny[x], nx[y], ny[y]));
}
inline void get4(int x) {
	double a2= epow2(nx[x], ny[x], nx[x + 1], ny[x + 1]);
	double b2= epow2(nx[x], ny[x], nx[x + 2], ny[x + 2]);
	double c2= epow2(nx[x + 1], ny[x + 1], nx[x + 2], ny[x + 2]);
	if(a2 + b2 == c2) nx[x + 3]= nx[x + 1] + nx[x + 2] - nx[x], ny[x + 3]= ny[x + 1] + ny[x + 2] - ny[x];
	if(a2 + c2 == b2) nx[x + 3]= nx[x] + nx[x + 2] - nx[x + 1], ny[x + 3]= ny[x] + ny[x + 2] - ny[x + 1];
	if(a2 == b2 + c2) nx[x + 3]= nx[x] + nx[x + 1] - nx[x + 2], ny[x + 3]= ny[x] + ny[x + 1] - ny[x + 2];
	return;
}
queue< int > qu;
int walkpast[500];
void SPFA() {
	qu.push(A * 4 - 1), qu.push(A * 4 - 2), qu.push(A * 4 - 3), qu.push(A * 4 - 4);
	dis[A * 4 - 1]= dis[A * 4 - 2]= dis[A * 4 - 3]= dis[A * 4 - 4]= 0;
	int nown;
	while(!qu.empty()) {
		nown= qu.front(), qu.pop();
		walkpast[nown]= 0;
		for(int i= 0; i < s * 4; i++) {
			if(i == nown) continue;
			if(dis[i] > dis[nown] + getd(i, nown) * (home(i, nown) ? T[nown / 4] : t)) {
				dis[i]= dis[nown] + getd(i, nown) * (home(i, nown) ? T[nown / 4] : t);
				if(!walkpast[i]) walkpast[i]= 1, qu.push(i);
			}
		}
	}
	return;
}
int main() {
	cin >> n;
	while(n--) {
		cin >> s >> t >> A >> B, ans= 1e10;
		for(int i= 0; i < s * 4; i++) {
			dis[i]= 1e10, walkpast[i]= 0;
			if(i % 4 == 3) {
				cin >> T[i / 4];
				get4(i - 3);
				continue;
			}
			cin >> nx[i] >> ny[i];
		}
		SPFA();
		for(int i= 1; i <= 4; i++) ans= min(ans, dis[B * 4 - i]);
		printf("%.1lf\n", ans);
	}
	return 0;
}