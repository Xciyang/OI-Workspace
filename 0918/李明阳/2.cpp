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
vector< EDGE > edg[100005];
struct NODE {
	int id, minx;
	inline int operator<(const NODE &n2) const {
		return minx > n2.minx;
	}
	inline int operator>(const NODE &n2) const {
		return id < n2.id;
	}
} node[100005];
int main() {
	read(n);
	for(int i= 1; i <= n; i++) node[i].id= i, node[i].minx= 0x3f3f3f3f;
	for(int i= 1; i < n; i++) {
		read(tmpx), read(tmpy), read(tmpz), edg[tmpx].push_back(EDGE{tmpy, tmpz});
		node[tmpx].minx= min(node[tmpx].minx, tmpz), node[tmpy].minx= min(node[tmpy].minx, tmpz);
	}
	sort(node + 1, node + n + 1);
	for(int i= 1; i <= n; i++) ans+= (long long)(n - i) * (node[i].minx + 1);
	sort(node + 1, node + n + 1, greater< NODE >());
	for(int i= 1; i <= n; i++)
		for(int j= 0; j < edg[i].size(); j++) ans= ans + edg[i][j].dis - (max(node[i].minx, node[edg[i][j].to].minx) + 1);
	put(ans), putchar('\n');
	return 0;
}