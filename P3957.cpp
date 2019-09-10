#include <iostream>
#include <stdio.h>
#include <string.h>
#include <deque>
using namespace std;
int n, d, k, x[500005], sc[500005], ans, f[500005], lasti;
int judge(int g) {
	memset(f, 0, sizeof(f)), lasti= 0;
	deque< int > qu;
	int maxs= d + g, mins= max(1, d - g);
	for(int i= 1; i <= n; i++) {
		for(; lasti < i && x[lasti] <= x[i] - mins; lasti++) {
			if(f[lasti] == -1) continue;
			while(!qu.empty() && f[qu.back()] <= f[lasti]) qu.pop_back();
			qu.push_back(lasti);
		}
		f[i]= -1;
		while(!qu.empty() && x[qu.front()] < x[i] - maxs) qu.pop_front();
		if(!qu.empty()) f[i]= f[qu.front()] + sc[i];
		if(f[i] >= k) return 1;
	}
	return 0;
}
int main() {
	cin >> n >> d >> k;
	for(int i= 1; i <= n; i++) cin >> x[i] >> sc[i];
	int l= 0, r= 1e6, mid;
	while(l < r) {
		mid= (l + r) >> 1;
		if(judge(mid))
			r= mid, ans= mid;
		else
			l= mid + 1;
	}
	cout << ans << endl;
	return 0;
}