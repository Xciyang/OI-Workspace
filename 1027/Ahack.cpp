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
#define N 100000

int n, m;
int main() {
	scanf("%d%d", &n, &m);
	string a, b;
	map< string, string > c;
	for(int i= 1; i <= n; i++) {
		cin >> a >> b;
		c[a]= b;
	}
	for(int i= 1; i <= m; i++) {
		cin >> a;
		for(int j= 1; j <= 4; j++) {
			cin >> b;
			if(c[a] == b) {
				printf("%c\n", 'A' + j - 1);
			}
		}
	}
	return 0;
}

/*

*/