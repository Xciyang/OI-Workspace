#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <vector>
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
int t, jl, last, n;
vector< int > v;
int main() {
    file("one");
	read(t);
	while(t--) {
		read(n);
		v.clear();
		for(int i= 1; i <= n; i++) v.push_back(i);
		last= 0, jl= 1;
		while(v.size() != 1) last= (last + jl - 1) % (int)v.size(), v.erase(v.begin() + last), ++jl;
        put(v[0]), putchar('\n');
	}
    return 0;
	// for(n= 3000; n <= 3000; n++) {
	// 	cout << n << ':';
	// 	v.clear();
	// 	for(int i= 1; i <= n; i++) v.push_back(i);
	// 	last= 0, jl= 1;
	// 	while(v.size() != 1) {
	// 		last= (last + jl - 1) % (int)v.size();
	// 		cout << '(' << last << ',' << v[last] << ')' << ' ';
	// 		v.erase(v.begin() + last);
	// 		++jl;
	// 	}
	// 	cout << endl << v[0] << endl;
	// }
	return 0;
}