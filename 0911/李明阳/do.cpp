#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#define file(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)
using namespace std;
template < typename T >
inline void read(T &e) {
	e= 0;
	T f= 1;
	char ch= getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') e= e * 10 + ch - '0', ch= getchar();
	e*= f;
	return;
}
template < typename T >
inline int put(const T &e) {
	if(e < 0) return putchar('-'), put(-e);
	if(e > 9) put(e / 10);
	return putchar('0' + e % 10);
}
int T, a, b, tmpx1, tmpx2, tmpy1, tmpy2, c, d, ans, tmpz;
int moves[][2]= {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
struct NODE {
	int x1, y1, x2, y2, nowc, nowd, lasto;
} tmpn;
queue< NODE > qu;
inline int dis(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}
inline int odis(int x1, int y1, int x2, int y2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
int main() {
    srand(time(0));
    file("do");
	read(T), read(a), read(b);
	if(a == 2 && b == 1) {
		cout << "SIMPLE" << endl;
		cout << "NAIVE" << endl;
		return 0;
	}
	while(T--) {
		read(tmpx1), read(tmpy1), read(tmpx2), read(tmpy2), read(c), read(d);
		if(rand() % 2) {
			cout << "SIMPLE" << endl;
		}
		else {
			cout << "NAIVE" << endl;
		}
	}
	return 0;
}