#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int n, c[27], t[1000006];
long long ans;
char A[1000006], B[1000006];
vector< int > v[27];
inline int lowb(int x) {
	return x & -x;
}
inline int query(int x) {
	int res= 0;
	for(; x; x-= lowb(x)) res+= t[x];
	return res;
}
inline void update(int x, int c) {
	for(; x <= n; x+= lowb(x)) t[x]+= c;
	return;
}
int main() {
	cin >> n >> (A + 1) >> (B + 1);
	for(int i= 1; i <= n; i++) v[A[i] - 'A'].push_back(i);
	for(int i= 1; i <= n; i++) {
		int x= query(v[B[i] - 'A'][c[B[i] - 'A']]);
		ans+= v[B[i] - 'A'][c[B[i] - 'A']] + x - i;
		update(1, 1), update(v[B[i] - 'A'][c[B[i] - 'A']], -1);
		++c[B[i] - 'A'];
	}
	cout << ans << endl;
	return 0;
}