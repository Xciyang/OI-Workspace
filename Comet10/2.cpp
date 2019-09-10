#include <iostream>
#include <stdio.h>
#include <map>
using namespace std;
int n, a[100005], cnt[5], tmpx, ts[100005];
map< int, int > mm;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) {
		cin >> a[i];
		tmpx= ++mm[a[i]], ++cnt[tmpx], --cnt[tmpx - 1];
	}
	if(cnt[3])
		cout << (n - cnt[3] * 3) / 2 + cnt[3] - 1 << endl;
	else if(cnt[2])
		cout << n - cnt[2] - 1 << endl;
	else
		cout << n << endl;
	return 0;
}