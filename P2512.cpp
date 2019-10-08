#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
long long n, a[1000006], b[1000006], sum, ans;
inline long long absl(long long x) {
	return x < 0 ? -x : x;
}
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i], sum+= a[i];
	sum/= n;
	for(int i= 1; i <= n; i++) b[i]= b[i - 1] + sum - a[i];
	sort(b + 1, b + n + 1); 
	for(int i= 1; i <= n; i++) ans+= absl(b[i] - b[n / 2]);
	cout << ans << endl;
	return 0;
}