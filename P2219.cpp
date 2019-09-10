#include <iostream>
#include <stdio.h>
#include <deque>
using namespace std;
int m, n, A, B, C, D, fw[1005][1005], psum[1005][1005], gy[1005][1005], ht[1005][1005];
int main() {
	cin >> n >> m >> A >> B >> C >> D;
	for(int i= 1; i <= n; i++)
		for(int j= 1; j <= m; j++) cin >> fw[i][j], psum[i][j]= psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1] + fw[i][j];
	for(int i= A; i <= n; i++)
		for(int j= B; j <= m; j++) gy[i][j]= psum[i][j] - psum[i - A][j] - psum[i][j - B] + psum[i - A][j - B];
	for(int i= C + 1; i <= n; i++)
		for(int j= D + 1; j <= m; j++) ht[i][j]= psum[i][j] - psum[i - C][j] - psum[i][j - D] + psum[i - C][j - D];
	for(int i= A; i <= n; i++) {
	}
	return 0;
}