#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
int n, k, cs[100005], l[100005], r[100005], cnt, cnt2;
char tmps[100005], w[]= "FN";
int judge(int x) {
	cnt= 0;
	for(int i= 1, j= 1, l= 0; i <= n; i++) {
		if(tmps[i] == tmps[j])
			++l;
		else
			l= 1, j= i;
		if(l > x) ++cnt, l= 0, j= i + 1;
	}
	return k >= cnt;
}
int main() {
	cin >> n >> k >> (tmps + 1);
	for(int i= 1; i <= n; i++) {
		if(tmps[i] != w[i & 1]) ++cnt;
		if(tmps[i] != w[(i & 1) ^ 1]) ++cnt2;
	}
	if(k >= cnt || k >= cnt2) {
		cout << 1 << endl;
		return 0;
	}
	int l= 2, r= n / k + 1, mid, ans= 2;
	while(l <= r) {
		mid= (l + r) >> 1;
		if(judge(mid))
			r= mid - 1, ans= mid;
		else
			l= mid + 1;
	}
	cout << ans << endl;
	return 0;
}