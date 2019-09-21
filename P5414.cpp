#include <iostream>
#include <stdio.h>
using namespace std;
int T, n, a[103], sum, f[103], ans;
int main() {
	cin >> T;
	while(T--) {
		cin >> n, sum= 0, ans= ~0x3f3f3f3f;
		for(int i= 1; i <= n; i++) cin >> a[i], sum+= a[i];
		for(int i= 1; i <= n; i++) {
			f[i]= max(0, a[i]);
			for(int j= 1; j < i; j++)
				if(a[i] >= a[j]) f[i]= max(f[i], f[j] + a[i]);
            ans= max(ans, f[i]);
		}
		cout << sum - ans << endl;
		/* code */
	}
	return 0;
}