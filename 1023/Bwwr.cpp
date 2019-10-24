#pragma region Header
#include <cmath>
#include <bitset>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <ctime>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
#define INF ((int)0x3F3F3F3F)
#define FINF ((int)0xC0C0C0C0)
#define llINF 0x3F3F3F3F3F3F3F3FLL
#define llFINF 0xC0C0C0C0C0C0C0C0LL
typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int UINT;
#define OJ_DBG(expr, str) (void)(!!(expr) || (puts(str), exit(0), 0))
#define ASSERT(expr) ((expr) || (puts("ASSERT failed expr:" #expr), exit(0), 0))
#define FREOPEN(s)                \
	freopen(s ".in", "r", stdin); \
	freopen(s ".out", "w", stdout);
#define IGNORE()                \
	while(c > '9' || c < '0') { \
		if(c == -1) return -1;  \
		if(c == '-') f= 0;      \
		c= getchar();           \
	}
#define READ(x, expr)             \
	while(c >= '0' && c <= '9') { \
		expr;                     \
		x= x * 10 + c - '0';      \
		c= getchar();             \
	}

inline int read() {
	int re= 0;
	bool f= 1;
	char c= getchar();
	IGNORE();
	READ(re, ;);
	return f ? re : -re;
}
inline LL readll() {
	LL re= 0;
	bool f= 1;
	char c= getchar();
	IGNORE();
	READ(re, ;);
	return f ? re : -re;
}
#pragma endregion
#define N 200200
int n, m;
int a[N];
int x[N];
#define PREV(p) ((p + n - 2) % n + 1)
#define NEXT(p) ((p) % n + 1)
// struct Node {
//	int p, f;
//	Node(int p, int f): p(p), f(f) {}
//};
// int solve(int v) {
//	queue<Node>q;
//}

int solver(int p, int v) {
	int ret= 0;
	for(int i= 0; i < n; i++, p= NEXT(p)) {
		int nxt= NEXT(p), nxt2= NEXT(nxt);
		if(x[nxt] == v) break;
		if(min(x[p], min(x[nxt], x[nxt2])) == v) {
			x[nxt]= v;
			++ret;
		}
		else if(max(x[p], max(x[nxt], x[nxt2])) == v) {
			x[nxt]= v;
			++ret;
		}
		else {
			break;
		}
	}
	return ret;
}
int solvel(int p, int v) {
	int ret= 0;
	for(int i= 0; i < n; i++, p= PREV(p)) {
		int pre= PREV(p), pre2= PREV(pre);
		if(x[pre] == v) break;
		if(min(x[p], min(x[pre], x[pre2])) == v) {
			x[pre]= v;
			++ret;
		}
		else if(max(x[p], max(x[pre], x[pre2])) == v) {
			x[pre]= v;
			++ret;
		}
		else {
			break;
		}
	}
	return ret;
}

int solve(int v) {
	int ans= 0;
	for(int i= 1; i <= n; i++) {
		if(x[i] == v) {
			ans+= solver(i, v);
			ans+= solvel(i, v);
		}
	}
	int p= 1;
	while(p <= n && x[p] != v) ++p;
	if(p > n) return -1;
	for(int i= 0; i < n; i++, p= NEXT(p)) {
		int nxt= NEXT(p), nxt2= NEXT(nxt), nxt3= NEXT(nxt2);
		if(x[nxt] != v) {
			if(min(x[p], min(x[nxt], x[nxt2])) == v) {
				x[nxt]= v;
				++ans;
			}
			else if(max(x[p], max(x[nxt], x[nxt2])) == v) {
				x[nxt]= v;
				++ans;
			}
			else if(x[p] < x[nxt] && x[nxt] > x[nxt2]) {
				x[nxt2]= max(x[nxt], x[nxt3]);
				x[nxt]= v;
				ans+= 2;
			}
			else if(x[p] > x[nxt] && x[nxt] < x[nxt2]) {
				x[nxt2]= min(x[nxt], x[nxt3]);
				x[nxt]= v;
				ans+= 2;
			} /* else {
				 ASSERT(0);
			 }*/
		}
	}
	return ans;
}

int main() {
	//	n = 5;
	//	int p = 1;
	//	while(1) {
	//		printf("%d\n", p);
	//		p = PREV(p);
	//	}
	n= read(), m= read();
	for(int i= 1; i <= n; i++) {
		a[i]= read();
	}
	for(int i= 1; i <= m; i++) {
		for(int j= 1; j <= n; j++) x[j]= a[j];
		printf("%d ", solve(i));
	}

	return 0;
}

/*
5 4
1 3 2 4 1


*/
