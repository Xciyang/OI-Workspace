#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
int n, nown, ans;
struct NODE {
	int c, t;
	inline int operator<(const NODE &n2) const {
		return t < n2.t;
	}
} a[150005];
priority_queue< int > qu;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i].c >> a[i].t;
	sort(a + 1, a + n + 1);
	for(int i= 1; i <= n; i++) {
		if(nown + a[i].c <= a[i].t) {
			++ans, nown+= a[i].c;
			qu.push(a[i].c);
		}
		else {
			if(qu.top() > a[i].c && nown - qu.top() + a[i].c <= a[i].t) {
				nown= nown - qu.top() + a[i].c;
				qu.pop(), qu.push(a[i].c);
			}
		}
	}
	cout << ans << endl;
	return 0;
}