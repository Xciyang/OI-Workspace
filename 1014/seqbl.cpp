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
#define OJ_DBG(expr,str) (void)(!!(expr)||(puts(str),exit(0),0))
#define ASSERT(expr) ((expr)||(fprintf(stderr,"ASSERT failed expr:" #expr),exit(0),0))
#define FREOPEN(s) freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);
#define IGNORE() while (c > '9' || c < '0') {if (c == -1)return -1;if (c == '-')f = 0;c = getchar();}
#define READ(x,expr) while (c >= '0' && c <= '9') {expr;x = x * 10 + c - '0';c = getchar();}

inline int read() {
	int re = 0;
	bool f = 1;
	char c = getchar();
	IGNORE();
	READ(re, ;);
	return f ? re : -re;
}
inline LL readll() {
	LL re = 0;
	bool f = 1;
	char c = getchar();
	IGNORE();
	READ(re, ;);
	return f ? re : -re;
}
#pragma endregion
int a[100100];
int a1[100100];
int a2[100100];
int cnt[2];
int n;
struct Pair {
	int a, b;
	Pair(int a, int b): a(a), b(b) {}
	bool operator < (const Pair&x)const {
		return min(a, b) < min(x.a, x.b);
	}
	int calc() {
		return (max(a, b) - min(a, b)) * 2;
	}
};
int calc1() { //121212121
	static int cntx[2];
	static bool flag[100100];
	for(int i = 1; i <= n; i++) {
		if((a[i] & 1) == (i & 1)) {
			flag[i] = 1;
			a1[i] = a[i];
		} else {
			cntx[a[i] & 1]++;
		}
	}
	if(cntx[0] != cntx[1])return INF;
	vector<Pair>vp;
	for(int i = 1; i <= n; i++) {
		if(flag[i])continue;
		for(int j = i + 1; j <= n; j++) {
			if(flag[j])continue;
			if((a[i] & 1) != (a[j] & 1)) {
				if(a[i] & 1)
					vp.push_back(Pair(i, j));
				else
					vp.push_back(Pair(j, i));
				flag[i] = flag[j] = 1;
				break;
			}
		}
		ASSERT(flag[i]);
	}
	sort(vp.begin(), vp.end());

//	ASSERT(vp.size() == cntx[0]);

	bool modify = 1;
	while(modify) {
		modify = 0;
		for(int i = 0; i < vp.size(); i++) {
			for(int j = i + 1; j < vp.size(); j++) {//ia ja ib jb -> ib ja ia jb  -> ib jb ia ja
				Pair x(vp[i].a, vp[j].b), y(vp[j].a, vp[i].b);
//				ASSERT(vp[i].calc() + vp[j].calc() >= x.calc() + y.calc());
				if(vp[i].calc() + vp[j].calc() >= x.calc() + y.calc()) {
					if(a[vp[j].b] < a[vp[i].b])
						vp[i] = x, vp[j] = y, modify = 1;
//					if(a[vp[j].a] < a[vp[i].a])
//						vp[i] = x, vp[j] = y, modify = 1;
				}
			}
		}
	}
	for(int i = 0; i < vp.size(); i++) {
		a1[vp[i].a] = a[vp[i].b];
		a1[vp[i].b] = a[vp[i].a];
	}
	int ret = 0;
	for(int i = 0; i < vp.size(); i++)
		ret += vp[i].calc();
	return ret;
}
int calc2() { //212121212
	int cntx[2] = {0};
	static bool flag[100100];
	for(int i = 1; i <= n; i++) {
		if((a[i] & 1) == ((i & 1) ^ 1)) {
			flag[i] = 1;
			a2[i] = a[i];
		} else {
			cntx[a[i] & 1]++;
		}
	}
	if(cntx[0] != cntx[1])return INF;
	vector<Pair>vp;
	for(int i = 1; i <= n; i++) {
		if(flag[i])continue;
		for(int j = i + 1; j <= n; j++) {
			if(flag[j])continue;
			if((a[i] & 1) != (a[j] & 1)) {
				if(a[i] & 1)
					vp.push_back(Pair(i, j));
				else
					vp.push_back(Pair(j, i));
				flag[i] = flag[j] = 1;
				break;
			}
		}
//		ASSERT(flag[i]);
	}
	sort(vp.begin(), vp.end());

//	ASSERT(vp.size() == cntx[0]);

	bool modify = 1;
	while(modify) {
		modify = 0;
		for(int i = 0; i < vp.size(); i++) {
			for(int j = i + 1; j < vp.size(); j++) {//ia ja ib jb -> ib ja ia jb  -> ib jb ia ja
				Pair x(vp[i].a, vp[j].b), y(vp[j].a, vp[i].b);
//				ASSERT(vp[i].calc() + vp[j].calc() >= x.calc() + y.calc());
				if(vp[i].calc() + vp[j].calc() >= x.calc() + y.calc()) {
					if(a[vp[j].b] < a[vp[i].b])
						vp[i] = x, vp[j] = y, modify = 1;
//					if(a[vp[j].a] < a[vp[i].a])
//						vp[i] = x, vp[j] = y, modify = 1;
				}
			}
		}
	}
	for(int i = 0; i < vp.size(); i++) {
		a2[vp[i].a] = a[vp[i].b];
		a2[vp[i].b] = a[vp[i].a];
	}
	int ret = 0;
	for(int i = 0; i < vp.size(); i++)
		ret += vp[i].calc();
	return ret;
}
int ans[100010];
int p[100010];
int main() {
//	FREOPEN("seq2");
	n = read();
	for(int i = 1; i <= n; i++) {
		p[i] = i;
		a[i] = read();
		cnt[a[i] & 1]++;
	}
	memset(ans, INF, sizeof(ans));
	int ansx = INF;
	do {
		int tmp = 0;
		for(int i = 1; i < n; i++) {
			if((a[p[i]] & 1) == (a[p[i + 1]] & 1)) {
				goto label_end;
			}
		}
		for(int i = 1; i <= n; i++)
			tmp += abs(p[i] - i);
		if(tmp < ansx) {
			ansx = tmp;
			for(int i = 1; i <= n; i++)
				ans[i] = a[p[i]];
		} else if(tmp == ansx) {
			for(int i = 1; i <= n; i++)
				if(a[p[i]] < ans[i]) {
					break;
				} else if(a[p[i]] > ans[i]) {
					goto label_end;
				}
			for(int i = 1; i <= n; i++)
				ans[i] = a[p[i]];
		}
label_end:
		;
	} while(next_permutation(p + 1, p + 1 + n));

//	int x1 = calc1();
//	int x2 = calc2();
//	int *ans = 0;
//	if(x1 == 0 || x2 == 0) {
//		ans = a;
//	} else if(x1 < x2) {
//		ans = a1;
//	} else if(x1 > x2) {
//		ans = a2;
//	} else {
//		for(int i = 1; i <= n; i++) {
//			if(a1[i] < a2[i]) {
//				ans = a1;
//				break;
//			}
//			if(a1[i] > a2[i]) {
//				ans = a2;
//				break;
//			}
//		}
//		if(ans == 0)ans = a1;
//	}
	for(int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	return 0;
}
/*
5
5 3 1 4 2

0011111000

*/




