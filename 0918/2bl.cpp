#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
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
int n, tmpx, tmpy, tmpz;
long long ans;
struct EDGE {
	int to, dis;
};
int minx[4005], edg[4005][4005];
int main() {
	read(n);
	for(int i= 1; i <= n; i++) minx[i]= 0x3f3f3f3f, edg[i][i]= 1;
	for(int i= 1; i < n; i++) {
		read(tmpx), read(tmpy), read(tmpz);
		minx[tmpx]= min(minx[tmpx], tmpz), minx[tmpy]= min(minx[tmpy], tmpz);
		edg[tmpx][tmpy]= edg[tmpy][tmpx]= 1, ans+= tmpz;
	}
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= n; j++) {
			if(edg[i][j]) continue;
			ans+= max(minx[i], minx[j]) + 1;
            edg[i][j]= edg[j][i]= 1;
		}
	}
	put(ans), putchar('\n');
	return 0;
}