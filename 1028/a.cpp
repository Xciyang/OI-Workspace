#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, a[5005], b[5005], bptr= 1, ans[5005];
int tmp[5005];
struct NODE {
	int w, val, dy;
	inline int operator<(const NODE &n2) const {
		return val > n2.val;
	}
} aa[5005], bb[5005];
inline int cmp(const NODE &n1, const NODE &n2) {
	return n1.w < n2.w;
}
inline int cmp2(const int &i1, const int &i2) {
	return b[aa[i1].dy] < b[aa[i2].dy];
}
inline int calc(int x, int y, int z, int k) {
	return (y > x) + (k > z);
}
int main() {
	freopen("a.out", "w", stdout);
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
begin:
	for(int i= 1; i <= n; i++) {
		for(int j= i + 1; j <= n; j++) {
			if(b[aa[i].dy] >= b[aa[j].dy]) continue;
			int res1= calc(aa[i].val, b[aa[i].dy], aa[j].val, b[aa[j].dy]);
			int res2= calc(aa[i].val, b[aa[j].dy], aa[j].val, b[aa[i].dy]);
			if(res1 <= res2) {
				swap(aa[i].dy, aa[j].dy);
				goto begin;
			}
		}
		ans[i]= b[aa[i].dy];
	}
	// for(int i= 1; i <= n; i++) {
	// 	int k= 0;
	// 	for(int j= i + 1; j <= n; j++) tmp[++k]= j;
	// 	sort(tmp + 1, tmp + k + 1, cmp2);
	// 	for(int l= 1, j; l <= k; l++) {
	// 		j= tmp[l];
	// 		if(b[aa[i].dy] >= b[aa[j].dy]) continue;
	// 		int res1= calc(aa[i].val, b[aa[i].dy], aa[j].val, b[aa[j].dy]);
	// 		int res2= calc(aa[i].val, b[aa[j].dy], aa[j].val, b[aa[i].dy]);
	// 		if(res1 <= res2) swap(aa[i].dy, aa[j].dy);
	// 	}
	// 	ans[i]= b[aa[i].dy];
	// }
	for(int i= 1; i <= n; i++) cout << ans[i] << ' ';
	cout << endl;
	return 0;
}
/*
9054 8846 8546 8534 9745 8741 8488 8442 8390 8290 8174 8153 7856 9427 7543 7502 212 9192 7295 7128 6881 4035 6878 6624 5968 5915 1511 6842 1295 5624 1244 1823 4024 5528 2246 3761 8049 5246 5195 4754 1149 2191 9050 7825 6909 2027 982 7259
*/
/*
47
*/
/*
10 
3 9 7 4 6 9 1 4 6 8 
1 10 7 7 7 1 7 1 9 4

7 10 9 7 7 1 4 7 1 1 
10 1 9 7 7 1 4 7 7 1

*/