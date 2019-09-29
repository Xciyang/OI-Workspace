#include <iostream>
#include <stdio.h>
using namespace std;
int n, k, h[100005], ans;

int main() {
	cin >> n >> k;
	for(int i= 1; i <= n; i++) {
		cin >> h[i];
		if(h[i] >= k) ++ans;
	}
	cout << ans << endl;
	return 0;
}