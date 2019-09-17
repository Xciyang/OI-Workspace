#include <iostream>
#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;
int n, m, q, u, v, t, qu[3][7000006], ta[3], he[3], sum, p;
#define gfront(x) (qu[(x)][ta[(x)]])

priority_queue< int > pu;
signed main() {
	scanf("%d%d%d%d%d%d", &n, &m, &q, &u, &v, &t);
	for(int i= 1; i <= n; i++) scanf("%d", qu[0] + i);
	sort(qu[0] + 1, qu[0] + n + 1, greater< int >()), he[0]= n;
	ta[0]= ta[1]= ta[2]= 1;
	for(int i= 1, nown; i <= m; i++) {
		if(ta[0] > he[0]) {
			if(gfront(1) > gfront(2))
				nown= gfront(1), ta[1]++;
			else
				nown= gfront(2), ta[2]++;
		}
		else if(gfront(0) >= gfront(1) && gfront(0) >= gfront(2))
			nown= gfront(0), ta[0]++;
		else if(gfront(1) >= gfront(0) && gfront(1) >= gfront(2))
			nown= gfront(1), ta[1]++;
		else
			nown= gfront(2), ta[2]++;
		nown+= sum;
		if(i % t == 0) printf("%d ", nown);
		sum+= q;
		qu[1][++he[1]]= (long long)nown * u / v - sum, qu[2][++he[2]]= nown - (long long)nown * u / v - sum;
	}
	printf("\n");
	for(int i= ta[0]; i <= he[0]; i++) pu.push(qu[0][i]);
	for(int i= ta[1]; i <= he[1]; i++) pu.push(qu[1][i]);
	for(int i= ta[2]; i <= he[2]; i++) pu.push(qu[2][i]);
	while(!pu.empty()) {
		++p;
		if(p % t == 0) printf("%d ", pu.top() + sum);
		pu.pop();
	}
	printf("\n");
	return 0;
}