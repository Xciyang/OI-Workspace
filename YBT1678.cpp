#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, pos[200005], al[200005], ar[200005], rak[200005], q, tmpx, tmpk, tmpt;
inline int pcmp(int x, int y) {
	return pos[x] < pos[y];
}
int main() {
	scanf("%d", &n);
	for(int i= 1; i <= n; i++) scanf("%d", pos + i);
	for(int i= 1; i <= n; i++) {
		scanf("%d", &tmpx);
		if(tmpx)
			ar[++ar[0]]= i;
		else
			al[++al[0]]= i;
	}
	sort(al + 1, al + al[0] + 1, pcmp), sort(ar + 1, ar + ar[0] + 1, pcmp);
	int a1= 1, a2= 1, cnt= 0;
	while(a1 <= al[0] && a2 <= ar[0]) rak[pos[al[a1]] < pos[ar[a2]] ? al[a1++] : ar[a2++]]= ++cnt;
	while(a1 <= al[0]) rak[al[a1++]]= ++cnt;
	while(a2 <= ar[0]) rak[ar[a2++]]= ++cnt;
	scanf("%d", &q);
	while(q--) {
		scanf("%d%d", &tmpk, &tmpt);
		int fp= rak[tmpk + 1], ans= 0;
		a1= a2= 1, cnt= 0;
		while(a1 <= al[0] && a2 <= ar[0] && cnt < fp) ans= (pos[al[a1]] - tmpt < pos[ar[a2]] + tmpt ? pos[al[a1++]] - tmpt : pos[ar[a2++]] + tmpt), ++cnt;
		if(a1 <= al[0] && cnt < fp) ans= pos[al[a1 + fp - cnt - 1]] - tmpt;
		if(a2 <= ar[0] && cnt < fp) ans= pos[ar[a2 + fp - cnt - 1]] + tmpt;
		printf("%d\n", ans);
	}
	return 0;
}