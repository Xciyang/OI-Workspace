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
int T, n, m, bestans;
struct NODE {
	int A, B, C;
	bool operator<(const NODE &n2) const {
		return (double)B / C > (double)n2.B / n2.C;
	}
} node[1005];
int F[3005];
int main() {
	file("score");
	read(T);
	while(T--) {
		read(n), read(m), bestans= 0;
		for(int i= 1; i <= n; i++) read(node[i].A), read(node[i].B), read(node[i].C);
		sort(node + 1, node + n + 1);
		memset(F, 0, sizeof(F));
		for(int i= 1; i <= n; i++)
			for(int j= m; j >= node[i].C; j--) F[j]= max(F[j], F[j - node[i].C] + node[i].A - node[i].B * j);
		for(int i= 1; i <= m; i++) bestans= max(bestans, F[i]);
		put(bestans), putchar('\n');
	}
	return 0;
}
/*
1
4 10
110 5 9
30 2 1
80 4 8
50 3 2

*/
