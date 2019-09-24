#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int n, v;
struct CAI {
	int c, a, b;
	inline int operator<(const CAI &c2) const {
		return a > c2.a;
	}
} cs[105];
int f[505][1200], ans;
int main() {
	cin >> n >> v;
	for(int i= 1; i <= n; i++) cin >> cs[i].c >> cs[i].a >> cs[i].b;
	memset(f, ~0x3f, sizeof(f));
	f[0][500]= 0;
	for(int i= 1; i <= n; i++) {
		if(cs[i].a < 0) {
			for(int k= -500; k <= 500 + cs[i].a; k++)
				for(int j= v; j >= cs[i].c; j--) f[j][k + 500]= max(f[j][k + 500], f[j - cs[i].c][k - cs[i].a + 500] + cs[i].b);
            // k - a > k
		}
		if(cs[i].a >= 0) {
			for(int k= 500; k >= -500 + cs[i].a; k--)
				for(int j= v; j >= cs[i].c; j--) f[j][k + 500]= max(f[j][k + 500], f[j - cs[i].c][k - cs[i].a + 500] + cs[i].b);
		}
	}
	for(int i= 0; i <= v; i++)
		for(int j= 0; j <= 500; j++) ans= max(ans, f[i][j + 500]);
	cout << ans << endl;
	return 0;
}