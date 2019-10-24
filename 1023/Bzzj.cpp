#pragma region revive
#include <set>
#include <map>
#include <list>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <initializer_list>
#define inl inline
#define re register int
#define fa(x) t[x].fa
#define son(x, y) t[x].child[y]
#define ls(x) t[x].child[0]
#define rs(x) t[x].child[1]
#define ll long long
#define ull unsigned long long
const int inf= 0x3f3f3f3f;
#define lowbit(x) ((x) & (-x))
using namespace std;
//#ifndef _DEBUG
//#define getchar() (*(IOB.in.p++))
//#define putchar(c) (*(IOB.out.p++) = (c))
//#define io_eof() (IOB.in.p >= IOB.in.pend)
// struct IOBUF {
//	struct {
//		char buff[1 << 27], *p, *pend;
//	} in;
//	struct {
//		char buff[1 << 27], *p;
//	} out;
//	IOBUF() {
//		in.p = in.buff;
//		out.p = out.buff;
//		in.pend = in.buff + fread(in.buff, 1, 1 << 27, stdin);
//	}
//	~IOBUF() { fwrite(out.buff, 1, out.p - out.buff, stdout); }
//} IOB;
//#endif
template < typename IO >
inl void write(IO x) {
	if(x == 0) return (void)putchar('0');
	if(x < 0) putchar('-'), x= -x;
	static char buf[30];
	char *p= buf;
	while(x) {
		*(p++)= x % 10 + '0';
		x/= 10;
	}
	while(p > buf) putchar(*(--p));
}
inl void writestr(const char *s) {
	while(*s != 0) putchar(*(s++));
}
template < typename IO >
inl void writeln(IO x) {
	write(x), putchar('\n');
}
template < typename IO >
inl void writesp(IO x) {
	write(x), putchar(' ');
}
inl int readstr(char *s) {
	char *begin= s, c= getchar();
	while(c < 33 || c > 127) {
		c= getchar();
	}
	while(c >= 33 && c <= 127) {
		*(s++)= c;
		c= getchar();
	}
	*s= 0;
	return s - begin;
}
template < typename IO >
inl IO read() {
	IO x= 0;
	register bool w= 0;
	register char c= getchar();
	while(c > '9' || c < '0') {
		if(c == '-') w= 1;
		c= getchar();
	}
	while(c >= '0' && c <= '9') {
		x= (x << 3) + (x << 1) + (c ^ 48);
		c= getchar();
	}
	return w ? -x : x;
}
template <>
inl double read< double >() {
	double x= 0;
	int w= 0, y= 0;
	ll z= 1;
	register char c= getchar();
	while(c > '9' || c < '0') {
		if(c == '-') w= 1;
		c= getchar();
	}
	while(c >= '0' && c <= '9' || c == '.') {
		if(c == '.') {
			y= 1, c= getchar();
			continue;
		}
		x= x * 10 + (c ^ 48);
		if(y) z*= 10;
		c= getchar();
	}
	return (w ? -x : x) / z;
}
#pragma endregion
#define P(x) ((x + n - 2) % n + 1)
#define N(x) (x % n + 1)
queue< int > q[10001];
int ori[10001], a[10001], n, m, ans, cnt;
inl int calc(int w) {
	ans= cnt= 0;
	for(re i= 1; i <= n; i++) a[i]= ori[i];
	while(q[w].size()) {
		re x= q[w].front(), pre1= P(x), pre2= P(pre1), pre3= P(pre2), nxt1= N(x), nxt2= N(nxt1), nxt3= N(nxt2);
		q[w].pop();
		if(max({a[x], a[pre1], a[pre2]}) == w || min({a[x], a[pre1], a[pre2]}) == w) {
			if(a[pre1] != w) q[w].push(pre1), ans++, a[pre1]= w;
		}
		if(max({a[x], a[nxt1], a[nxt2]}) == w || min({a[x], a[nxt1], a[nxt2]}) == w) {
			if(a[nxt1] != w) q[w].push(nxt1), ans++, a[nxt1]= w;
		}
	}
	for(re i= 1; i <= n; i++)
		if(a[i] == w) q[w].push(i);
	while(q[w].size()) {
		re x= q[w].front(), pre1= P(x), pre2= P(pre1), pre3= P(pre2), nxt1= N(x), nxt2= N(nxt1), nxt3= N(nxt2);
		q[w].pop();
		if(a[pre1] > a[x] && a[pre2] < a[x]) {
			a[pre2]= max(a[pre1], a[pre3]), ans++;
		}
		else if(a[pre1] < a[x] && a[pre2] > a[x]) {
			a[pre2]= min(a[pre1], a[pre3]), ans++;
		}
		if(max({a[x], a[pre1], a[pre2]}) == w || min({a[x], a[pre1], a[pre2]}) == w) {
			if(a[pre1] != w) q[w].push(pre1), ans++, a[pre1]= w;
		}
		if(a[nxt1] > a[x] && a[nxt2] < a[x]) {
			a[nxt2]= max(a[nxt1], a[nxt3]), ans++;
		}
		else if(a[nxt1] < a[x] && a[nxt2] > a[x]) {
			a[nxt2]= min(a[nxt1], a[nxt3]), ans++;
		}
		if(max({a[x], a[nxt1], a[nxt2]}) == w || min({a[x], a[nxt1], a[nxt2]}) == w) {
			if(a[nxt1] != w) q[w].push(nxt1), ans++, a[nxt1]= w;
		}
	}
	for(re i= 1; i <= n; i++)
		if(a[i] != w) return -1;
	return ans;
}
signed main() {
	n= read< int >(), m= read< int >();
	for(re i= 1; i <= n; i++) ori[i]= read< int >(), q[ori[i]].push(i);
	for(re i= 1; i <= m; i++) writesp(calc(i));
}
