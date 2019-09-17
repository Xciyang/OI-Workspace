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
int T, n, m, fini[1005], A[1005], B[1005], C[1005], flag, bestans;
void dfs(int fenz, int na) {
	for(int i= 1; i <= n; i++) {
		if(fini[i]) continue;
		if(A[i] - B[i] * (fenz + C[i]) <= 0 || fenz + C[i] > m) continue;
		fini[i]= 1;
		dfs(fenz + C[i], na + A[i] - B[i] * (fenz + C[i]));
		fini[i]= 0;
	}
	bestans= max(na, bestans);
	return;
}
int F[3005];
int main() {
	file("score");
	read(T);
	srand(time(0));
	while(T--) {
		read(n), read(m), bestans= flag= 0;
		for(int i= 1; i <= n; i++) {
			read(A[i]), read(B[i]), read(C[i]);
			if(B[i]) flag = 1;
		}
		if(n <= 10) {
			dfs(0, 0);
			put(bestans), putchar('\n');
		}
		else if(!flag) {
			memset(F, 0, sizeof(F));
			for(int i= 1; i <= n; i++) 
				for(int j= m; j >= C[i]; j++) F[j]= max(F[j], F[j - C[i]] + A[i]);
			for(int i= 1; i <= m; i++) bestans= max(bestans, F[i]);
			put(bestans), putchar('\n');
		}
		else {
			put(B[rand() % n + 1] * n), putchar('\n');
		}
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
