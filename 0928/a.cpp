#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
int n, m, a[100005], cptr= 1, c[100005];
int main() {
	cin >> n >> m;
	for(int i= 1; i <= m; i++) cin >> a[i], c[a[i]]= 1;
	if(m == 0) {
		for(int i= 1; i <= n; i++) cout << i << endl;
		return 0;
	}
	for(int i= 1; i <= n; i++) {
		if(c[i]) continue;
		while(cptr <= m && i > a[cptr]) {
			cout << a[cptr] << endl;
			++cptr;
		}
		cout << i << endl;
	}
	while(cptr <= m) {
		cout << a[cptr] << endl;
		++cptr;
	}
	return 0;
}