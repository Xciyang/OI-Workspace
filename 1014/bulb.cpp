#include <iostream>
#include <stdio.h>
using namespace std;
int n, q, k, c[200005], tmpx, w[200005], ans, cnt;
int main() {
	cin >> n >> q >> k;
	for(int i= 1; i <= n; i++) cin >> c[i];
	while(q--) {
		cin >> tmpx;
		w[tmpx]^= 1;
		ans= cnt= 0;
		for(int i= 1; i <= n; i++) {
			if(w[c[i]])
				++cnt;
			else if(cnt)
				cnt= 0, ++ans;
		}
		if(cnt) ++ans;
		cout << ans << endl;
	}
	return 0;
}