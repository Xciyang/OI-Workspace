#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <limits.h>
#include <queue>
using namespace std;
long long n, ans= LONG_LONG_MAX;
int main() {
	cin >> n;
	for(long long x= 1; x * x <= n; x++)
		if(n % x == 0) ans= min(ans, x + n / x - 2);
	cout << ans << endl;
	return 0;
}
