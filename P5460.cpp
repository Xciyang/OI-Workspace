#include <iostream>
#include <stdio.h>
#include <vector>
#define int unsigned int
using namespace std;
int n, q, ch[5000006][2], cptr, v[5000006], lazyc[5000006], tags[5000006], rt, ans[5000006];
char opt[100005];
struct BIT {
	int num, len;
} s[100005], ips[100005];
inline char getopt() {
	char ch= getchar();
	return (ch == 'A' || ch == 'D' ? ch : getopt());
}
inline BIT getbit() {
	char ch= getchar();
	int e= 0, len= 0;
	while(ch < '0' || ch > '9') ch= getchar();
	while(ch == '0' || ch == '1') e+= (ch - '0') << len, ++len, ch= getchar();
	return BIT{e, len};
}
inline int getnum() {
	char ch= getchar();
	int e= 0;
	while(ch < '0' || ch > '9') ch= getchar();
	while(ch >= '0' && ch <= '9') e= e * 10 + ch - '0', ch= getchar();
	return e;
}
inline int putnum(int e) {
	if(e > 9) putnum(e / 10);
	return putchar('0' + e % 10);
}
vector< int > bq[100005], eq[100005];
inline void update(int nown, int c) {
	if(!tags[nown]) v[nown]+= c, lazyc[nown]+= c;
	return;
}
inline void pushd(int nown) {
	if(!ch[nown][0]) ch[nown][0]= ++cptr;
	if(!ch[nown][1]) ch[nown][1]= ++cptr;
	update(ch[nown][0], lazyc[nown]), update(ch[nown][1], lazyc[nown]), lazyc[nown]= 0;
	return;
}
void add(int &nown, int x, int len) {
	if(!nown) nown= ++cptr;
	if(!len) {
		update(nown, 1), ++tags[nown];
		return;
	}
	if(lazyc[nown]) pushd(nown);
	add(ch[nown][x & 1], x >> 1, len - 1);
	return;
}
void del(int &nown, int x, int len) {
	if(!nown) nown= ++cptr;
	if(!len) {
		--tags[nown], update(nown, 1);
		return;
	}
	if(lazyc[nown]) pushd(nown);
	del(ch[nown][x & 1], x >> 1, len - 1);
	return;
}
int query(int nown, int x, int len) {
	if(!nown) return 0;
	if(!len) return v[nown];
	if(lazyc[nown]) pushd(nown);
	return query(ch[nown][x & 1], x >> 1, len - 1);
}
signed main() {
	n= getnum(), q= getnum();
	for(int i= 1; i <= n; i++) opt[i]= getopt(), s[i]= getbit();
	for(int i= 1; i <= q; i++) ips[i]= getbit(), bq[getnum()].push_back(i), eq[getnum()].push_back(i);
	for(int i= 1; i <= n; i++) {
		opt[i] == 'A' ? add(rt, s[i].num, s[i].len) : del(rt, s[i].num, s[i].len);
		for(int j= 0; j < (int)bq[i].size(); j++) ans[bq[i][j]]-= query(rt, ips[bq[i][j]].num, ips[bq[i][j]].len);
		for(int j= 0; j < (int)eq[i].size(); j++) ans[eq[i][j]]+= query(rt, ips[eq[i][j]].num, ips[eq[i][j]].len);
	}
	for(int i= 1; i <= q; i++) putnum(ans[i]), putchar('\n');
	return 0;
}