#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m, d[1000], pos[1000], ssum[1000][1000], yx[1000][1000], f[505][505], ans;
// d_i => i - 1 ~ i
int main() {
	cin >> n >> m;
    pos[0]= ~0x3f3f3f3f;
	for(int i= 2; i <= n; i++) cin >> d[i], pos[i]= pos[i - 1] + d[i];
	for(int i= 0; i <= n; i++)
		for(int j= i + 1; j <= n; j++)
			for(int k= i + 1; k <= j; k++) {
				ssum[i][j]+= pos[k] - pos[i];
				if(pos[k] - pos[i] > pos[j] - pos[k]) yx[i][j]+= pos[k] - pos[i] - pos[j] + pos[k];
			}
	memset(f, 0x3f, sizeof(f));
	for(int i= 1; i <= n; i++) f[i][1]= ssum[0][i] - yx[0][i];
	for(int k= 2; k <= m; k++) {
		for(int i= 1; i <= n; i++) {
			for(int j= k - 1; j < i; j++) {
				f[i][k]= min(f[i][k], f[j][k - 1] + ssum[j][i] - yx[j][i]);
			}
		}
	}
    ans= 0x3f3f3f3f;
    for(int i= 1; i <= n; i++) ans= min(ans, f[i][m] + ssum[i][n]);
	cout << ans << endl;
	return 0;
}