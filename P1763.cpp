#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m, f[1 << 10][100], ans;
char tmp[10][10];
int scx[10], scy[10], sptr, walkpast[10][10], cnt;
inline int limit(int x, int y) {
	return x > -1 && y > -1 && x < n && y < m;
}
int calc() {
	memset(f, 0, sizeof(f)), f[0][0]= 1, sptr= 0;
	for(int i= 0; i < n; i++)
		for(int j= 0; j < m; j++)
			if(tmp[i][j] == 'X') scx[sptr]= i, scy[sptr]= j, ++sptr;
	for(int i= 0; i < (1 << sptr); i++) {
		memset(walkpast, 1, sizeof(walkpast)), cnt= n * m;
		for(int j= 0; j < sptr; j++) {
			if(i & (1 << j)) continue;
			for(int x= -1; x <= 1; x++)
				for(int y= -1; y <= 1; y++)
					if(limit(scx[j] + x, scy[j] + y) && walkpast[scx[j] + x][scy[j] + y]) walkpast[scx[j] + x][scy[j] + y]= 0, --cnt;
		}
		for(int j= 0; j <= cnt; j++) {
			if(!f[i][j]) continue;
			f[i][j + 1]= (f[i][j + 1] + f[i][j] * (cnt - j)) % 12345678;
			for(int k= 0; k < sptr; k++) {
				if(i & (1 << k)) continue;
				f[i | (1 << k)][j + 1]= (f[i | (1 << k)][j + 1] + f[i][j]) % 12345678;
			}
		}
	}
	return f[(1 << sptr) - 1][n * m];
}
void DFS(int x, int y, int k) {
	if(x == n) {
		ans= (ans + k * calc()) % 12345678;
		return;
	}
	if(y == m) {
		DFS(x + 1, 0, k);
		return;
	}
	DFS(x, y + 1, k);
	for(int i= -1; i <= 1; i++)
		for(int j= -1; j <= 1; j++)
			if(limit(x + i, y + j) && tmp[x + i][y + j] == 'X') return;
	tmp[x][y]= 'X';
	DFS(x, y + 1, -k);
	tmp[x][y]= '.';
	return;
}
int main() {
	cin >> n >> m;
	for(int i= 0; i < n; i++)
		for(int j= 0; j < m; j++) cin >> tmp[i][j];
	for(int x= 0; x < n; x++) {
		for(int y= 0; y < m; y++) {
			if(tmp[x][y] == 'X')
				for(int i= -1; i <= 1; i++)
					for(int j= -1; j <= 1; j++)
						if((i || j) && limit(x + i, y + j) && tmp[x + i][y + j] == 'X') return cout << 0 << endl, 0;
		}
	}
	DFS(0, 0, 1);
	cout << (ans + 12345678) % 12345678 << endl;
	return 0;
}