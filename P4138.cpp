#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int n, m, F[2005][2005], ans;
struct GS {
	int a, b;
	inline int operator<(const GS &g2) const {
		return a > g2.a;
	}
} gs[2005];
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> gs[i].a >> gs[i].b;
	memset(F, ~0x3f, sizeof(F));
	sort(gs + 1, gs + n + 1);
	F[0][0]= F[0][1]= 0;
	for(int i= 1; i <= n; i++)
		for(int j= 0; j <= n; j++) F[i][j]= max(F[i - 1][j], F[i - 1][max(j - gs[i].a, 0) + 1] + gs[i].b);
	for(int i= 0; i <= n; i++) ans= max(ans, F[n][i]);
	cout << ans << endl;
	return 0;
}