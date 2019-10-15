#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
int n, a[100005], cnt;
double ans, tmpx, tmpy, tmpz;
long long tot, nowt;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i], tot+= a[i];
	if(n == 1)
		ans= a[1];
	else if(n <= 20) {
		for(int ss= (1 << n) - 1; ss; ss= ((ss - 1) & ((1 << n) - 1))) {
			++cnt, tmpx= tmpy= 1, nowt= tot;
			for(int i= 1; i <= n; i++)
				if((ss >> (i - 1)) & 1) tmpx*= a[i], tmpy*= nowt, nowt-= a[i];
			if(ss & 1) ans+= tmpx * (tot - nowt) / tmpy;
		}
	}
	else {
	}
	printf("%.7lf\n", ans);
	return 0;
}