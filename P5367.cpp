#include <iostream>
#include <stdio.h>
using namespace std;
int n, a[1000001], ans, b[1000001], jc= 1;
#define lowb(a) ((a) & -(a))
inline void update(int x) {
	for(; x <= n; x+= lowb(x)) ++b[x];
}
inline int query(int x) {
	int ans= 0;
	for(; x; x-= lowb(x)) ans+= b[x];
	return ans;
}
int main() {
	cin >> n;
	for(int i= n; i; i--) cin >> a[i];
	for(int i= 1; i <= n; i++) ans= ((long long)query(a[i]) * jc + ans) % 998244353, jc= (long long)jc * i % 998244353, update(a[i]);
	cout << ans + 1 << endl;
	return 0;
}