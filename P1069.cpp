#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m1, m2, ans= 0x3f3f3f3f, w[30005];
long long s[10004], g[30005], g2[30005], tmpx;
int main() {
	cin >> n >> m1 >> m2;
	for(int i= 2; i * i <= m1; i++)
		while(m1 % i == 0) m1/= i, g[i]+= m2;
	if(m1 > 1) g[m1]+= m2;
	for(int i= 1; i <= 30000; i++)
		if(g[i]) w[++w[0]]= i;
	for(int i= 1; i <= n; i++) {
		cin >> tmpx;
		memset(g2, 0, sizeof(g2));
		for(long long j= 2; j * j <= tmpx; j++) {
			if(j > w[w[0]]) break;
			while(tmpx % j == 0) tmpx/= j, ++g2[j];
		}
		if(tmpx > 1 && tmpx <= w[w[0]]) ++g2[tmpx];
		int res= 0, flag= 1;
		for(int j= 1; j <= w[0]; j++) {
			if(g2[w[j]] == 0) {
				flag= 0;
				break;
			}
			res= max((long long)res, g[w[j]] / g2[w[j]] + (g[w[j]] % g2[w[j]] != 0));
		}
		if(!flag) continue;
		ans= min(ans, res);
	}
	cout << (ans == 0x3f3f3f3f ? -1 : ans) << endl;
	return 0;
}