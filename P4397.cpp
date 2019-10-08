#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, zs[100005], flag[100005];
inline void shai() {
	for(int i= 2; i <= 100000; i++) {
		if(!flag[i]) zs[++zs[0]]= i;
		for(int j= 1; j <= zs[0] && i * zs[j] <= 100000; j++) {
			flag[i * zs[j]]= 1;
			if(i % zs[j] == 0) break;
		}
	}
	return;
}
int ans[100005];
inline int isZS(int x) {
	if(x <= 100000) return !flag[x];
	for(int i= 1; zs[i] * zs[i] <= x; i++)
		if(x % zs[i] == 0) return x == zs[i];
	return 1;
}
void dfs(int nown, int lasti, int y) {
	if(nown == 1) {
		ans[++ans[0]]= y;
		return;
	}
	if(nown - 1 >= zs[lasti] && isZS(nown - 1)) ans[++ans[0]]= y * (nown - 1);
	for(int i= lasti; i <= zs[0] && zs[i] * zs[i] <= nown; i++) {
		for(long long j= zs[i], res= 1 + zs[i]; res <= nown; j*= zs[i], res+= j)
			if(nown % res == 0) dfs(nown / res, i + 1, y * j);
	}
}
int main() {
	shai();
	while(cin >> n) {
		ans[0]= 0, dfs(n, 1, 1);
		sort(ans + 1, ans + ans[0] + 1);
		cout << ans[0] << endl;
		for(int i= 1; i <= ans[0]; i++) {
			cout << ans[i] << ' ';
			if(i == ans[0]) putchar('\n');
		}
	}
	return 0;
}