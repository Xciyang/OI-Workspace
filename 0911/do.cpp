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
int T, a, b, tmpx1, tmpx2, tmpy1, tmpy2, c, d, ans, tmpz, nx, ny;
int moves[][2]= {{-1, 0}, {0, -1}, {0, 1}, {1, 0}, {0, 0}};
inline int odis(int x1, int y1, int x2, int y2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
int main() {
	read(T), read(a), read(b);
	while(T--) {
		read(tmpx1), read(tmpy1), read(tmpx2), read(tmpy2), read(c), read(d);
		tmpx2= tmpx1 + abs(tmpx1 - tmpx2), tmpy2= tmpy1 + abs(tmpy1 - tmpy2);
		while(true) {
			if(d <= 0) {
				cout << "NAIVE" << endl;
				break;
			}
			if(tmpx1 == tmpx2 && tmpy1 == tmpy2) {
				cout << "SIMPLE" << endl;
				break;
			}
			if(c >= a) {
				d-= odis(tmpx1, tmpy1, tmpx2, tmpy2), c-= a;
				if(d <= 0) {
					cout << "NAIVE" << endl;
					break;
				}
			}
			else {
				c+= b;
			}
			for(int i= 0; i < 2; i++) {
				if(abs(tmpy1 - tmpy2) > abs(tmpx1 - tmpx2)) {
					--tmpy2;
				}
				else {
					--tmpx2;
				}
				if(tmpx1 == tmpx2 && tmpy1 == tmpy2) break;
			}
		}
	}
	return 0;
}