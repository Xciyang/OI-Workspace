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
int n, m, la[100005] /*, p[], ans */;
struct EDGE {
	int to, dis;
};
int res;
struct NODE {
	int id, x;
	bool operator<(const NODE &n2) const {
		return x < n2.x;
	}
} a[100005], b[100005];
int main() {
	// cin >> n;
	// for(int i= 1; i <= n; i++) {
	// 	cin >> a[i].x;
	// 	a[i].id= i;
	// 	la[i]= a[i].x;
	// }
	// for(int i= 1; i <= n; i++) {
	// 	cin >> b[i].x;
	// 	b[i].id= i;
	// }
	// sort(a + 1, a + n + 1);
	// sort(b + 1, b + n + 1);
	// for(int i= 1; i <= n; i++) {
	// 	if(a[i].x > b[i].x) {
	// 		cout << "No" << endl;
	// 		return 0;
	// 	}
	// }
	// cout << "Yes" << endl;
    cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i], aa[i].w= i, aa[i].val= a[i];
	for(int i= 1; i <= n; i++) cin >> b[i];
	sort(aa + 1, aa + n + 1);
	sort(b + 1, b + n + 1, greater< int >());
	for(int i= 1; i <= n; i++) {
		if(b[bptr] <= aa[i].val) continue;
		aa[i].dy= bptr;
		++bptr;
	}
	sort(aa + 1, aa + n + 1, cmp);
	for(int i= 1; i <= n; i++) {
		if(aa[i].dy) continue;
		aa[i].dy= bptr;
		++bptr;
	}
	return 0;
}