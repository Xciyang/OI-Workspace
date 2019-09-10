#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, hangl[15], ans;
char instr[30];
inline int lowb(int x) {
	return x & -x;
}
void dfs(int hang, int lim1, int lim2, int lie) {
	if(lie == m) {
		++ans;
		return;
	}
	int allp= m & ~(lie | lim1 | lim2 | hangl[hang]);
	while(allp) {
		int p= lowb(allp);
		dfs(hang + 1, (lim1 + p) << 1, (lim2 + p) >> 1, lie + p);
		allp-= p;
	}
	return;
}
int main() {
	cin >> n;
	m= (1 << n) - 1;
	for(int i= 0; i < n; i++) {
		cin >> (instr + 1);
		for(int j= 1; j <= n; j++)
			if(instr[j] == '.') hangl[i]|= (1 << (n - j));
	}
	dfs(0, 0, 0, 0);
	cout << ans << endl;
	return 0;
}