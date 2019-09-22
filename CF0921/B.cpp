#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
struct NODE {
	int x, id;
	inline int operator<(const NODE &n2) const {
		return x > n2.x;
	}
} ns[1005];
int n, ans2[1005];
long long ans;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> ns[i].x, ns[i].id= i;
	sort(ns + 1, ns + n + 1);
	for(int i= 1; i <= n; i++) ans+= (long long)ns[i].x * (i - 1) + 1, ans2[i]= ns[i].id;
	cout << ans << endl;
	for(int i= 1; i <= n; i++) cout << ans2[i] << ' ';
	cout << endl;
	return 0;
}