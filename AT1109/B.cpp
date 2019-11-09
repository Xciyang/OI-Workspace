#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <string.h>
#include <vector>
#include <queue>
#include <map>
using namespace std;
inline int lowb(int x) {
	return x & -x;
}
int n, m, a[100005], b[100005] /*, p[], ans */;
struct EDGE {
	int to, dis;
};
long long ans= 1;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) {
		cin >> a[i];
		if((a[i] != 0 && i == 1) || (a[i] == 0 && i != 1)) {
			cout << 0 << endl;
			return 0;
		}
	}
	sort(a + 1, a + n + 1);
	b[0]= 1;
	for(int i= 1; i <= n; i++) {
		ans= ans * b[a[i]] % 998244353, ++b[a[i] + 1];
	}
	cout << ans << endl;
	return 0;
}