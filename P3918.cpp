#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, k, c[305], ans[1005], l, r, last[1005];
long long res;
int main() {
	cin >> n >> k;
	for(int i= 1; i <= k; i++) cin >> c[i];
	sort(c + 1, c + k + 1, greater< int >());
	for(l= 1, r= n; l <= r; l++, r--) ans[l]= ans[r]= min(l, k);
	for(int i= 1; i <= n; i++) {
		if(last[ans[i]]) res= res + (i - last[ans[i]]) * c[ans[i]];
		last[ans[i]]= i;
	}
	cout << res << endl;
	return 0;
}