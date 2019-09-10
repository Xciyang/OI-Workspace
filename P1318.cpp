#include <iostream>
#include <stdio.h>
using namespace std;
int n, x[10005], f[2][10005], ans;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> x[i];
	for(int i= 1; i <= n; i++) f[0][i]= max(f[0][i - 1], x[i]);
	for(int i= n; i >= 1; i--) f[1][i]= max(f[1][i + 1], x[i]);
	for(int i= 1; i <= n; i++)
		if(min(f[0][i], f[1][i]) - x[i] > 0) ans+= min(f[0][i], f[1][i]) - x[i];
	cout << ans << endl;
	return 0;
}