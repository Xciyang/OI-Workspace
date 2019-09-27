#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
int n, h[4005], f[4005][4005], ans= 0x3f3f3f3f, lastt;
vector< int > no[4005];
void init() {
	int nowx, nowy;
	for(int i= 1; i <= n; i++) {
		nowx= i, nowy= h[i];
		while(nowx < n && nowy > h[nowx + 1]) {
			++nowx, --nowy;
			if(nowy == h[nowx]) {
				lastt= i, no[nowx].push_back(i);
				break;
			}
		}
	}
	return;
}
/*
10
4 0 0 0 0 3 0 0 0 1

16
4 0 0 0 0 4 0 0 0 0 4 0 0 0 0 0
13


10
4 2 0 0 0 4 2 0 0 0

*/
int to[4005];
void dfsinit() {
	int nowx, nowy;
	for(int i= 1; i <= n; i++) {
		nowx= i, nowy= h[i];
		while(nowx < n && nowy > h[nowx + 1]) {
			++nowx, --nowy;
			if(nowy == h[nowx]) {
				to[i]= nowx;
				break;
			}
		}
	}
	return;
}
int dfsans= 0x3f3f3f3f;
int wp[10000];
void dfs(int nowx, int nowy, int step) {
	if(step >= dfsans) return;
	if(nowx >= n && nowy >= n) {
		for(int i= 1; i < n; i++)
			if(!wp[i]) return;
		dfsans= step;
		return;
	}
	int lwpx= wp[nowx], lwpy= wp[nowy];
	wp[nowx]= 1, wp[nowy]= 1;
	dfs(nowx + 1, nowy + 1, step + 1);
	if(to[nowx]) dfs(to[nowx], nowy + 1, step + 1);
	if(to[nowy]) dfs(nowx + 1, to[nowy], step + 1);
	if(to[nowx] && to[nowy]) dfs(to[nowx], to[nowy], step + 1);
	wp[nowx]= lwpx, wp[nowy]= lwpy;
	return;
}
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> h[i];
	dfsinit(), dfs(1, 1, 1);
	cout << dfsans << endl;
	return 0;
}
int main2() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> h[i];
	init(), memset(f, 0x3f, sizeof(f)), f[0][0]= 0;
	for(int i= 1; i <= n; i++) {
		for(int j= 0; j < i; j++) f[i][j + 1]= f[i - 1][j] + 1;
		for(int k= 0, l; k < no[i].size(); k++) {
			l= no[i][k];
			for(int j= 0; j < i; j++) f[i][j + 1]= min(f[i][j + 1], f[l][j] + i - l);
			for(int j= 0; j < i; j++) f[i][j + i - l]= min(f[i][j + i - l], f[l][j] + 1);
		}
	}
	for(int i= 1; i <= n; i++) ans= min(ans, max(i, f[n][i]));
	cout << ans << endl;
	return 0;
}