#include <cmath>
#include <cstdio>
#include <cctype>
#include <ciso646>
#include <cstring>
#include <algorithm>
#define inl inline
#define mset(x, y) memset(x, y, sizeof(x))
#define mcpy(x, y) memcpy(x, y, sizeof(y))
using std::max;
typedef double db;
typedef long long ll;
inl char gc() {
	const static int len= 1 << 21 | 1;
	static char buf[len], *p1= buf, *p2= buf;
	return (p1 == p2 and (p2= (p1= buf) + fread(buf, 1, len, stdin), p1 == p2)) ? -1 : *p1++;
}
template < typename T >
inl bool rd(T &r) {
	r= 0;
	bool neg= 0;
	char c= gc();
	while(!isdigit(c) and ~c) neg= (c == '-'), c= gc();
	while(isdigit(c)) r= 10 * r + c - '0', c= gc();
	if(neg) r= -r;
	return ~c;
}
template < typename T, typename... A >
inl bool rd(T &t, A &... a) {
	return rd(t), rd(a...);
}
const int MAX_N= 100005;
bool son[MAX_N];
int cnt[MAX_N];
int dep[MAX_N];
int fa[MAX_N];
int n;
int calc(int i) {
	if(i == 1) return 0;
	if(dep[i]) return dep[i];
	return dep[i]= calc(fa[i]) + 1;
}
int main() {
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	rd(n);
	for(int i= 2; i <= n; ++i) {
		rd(fa[i]);
		son[fa[i]]= 1;
	}
	for(int i= 2; i <= n; ++i) calc(i);
	for(int i= 2; i <= n; ++i)
		if(!son[i]) ++cnt[fa[i]];
	for(int i= 2; i <= n; ++i)
		if(son[i]) cnt[i]+= cnt[fa[i]];
	for(int i= 1; i <= n; ++i)
		if(cnt[i] > dep[i] + 1) return puts("Y"), 0;
	puts("D");
	return 0;
}