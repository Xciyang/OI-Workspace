#include <iostream>
#include <cstdio>
using namespace std;
int n, a[100005], ans[100005], cnt;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i];
	for(int i= 1; i <= n + 1; i++)
		if(a[i] < a[i - 1]) ans[i - 1]= ++cnt;
	for(int i= n; i >= 1; i--)
		if(!ans[i]) ans[i]= ++cnt;
	for(int i= n; i >= 1; i--) cout << ans[i] << ' ';
	return 0;
}