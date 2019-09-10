#include <iostream>
#include <stdio.h>
#include <string.h>
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
int t;
namespace BL {
int b[100005];
void work() {
	int n, m, q, ans;
	while(t--) {
		read(n), read(m), read(q);
		memset(b, 0, sizeof(b)), ans= 0;
		for(int cntx= 0; cntx <= q; cntx+= n)
			for(int cnty= 0; cntx + cnty <= q; cnty+= m)
				if(!b[cntx + cnty]) b[cntx + cnty]= 1, ++ans;
		put(q - ans + 1), putchar('\n');
	}
	return;
}
}  // namespace BL
int main() {
	file("simple");
	read(t);
	BL::work();
	return 0;
}