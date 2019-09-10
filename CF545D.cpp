#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, a[100005], sum, ans;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	for(int i= 1; i <= n; i++)
		if(sum <= a[i]) ++ans, sum+= a[i];
	cout << ans << endl;
	return 0;
}