#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int n, m;
char tmps[805][805];
vector< int > v1[805], v2[805];
int ans[805 * 2][805 * 2];
inline void set1(int x, int y) {
	ans[(x - 1) * 2 + 1][y * 2]= 1;
}
inline void set2(int x, int y) {
	ans[x * 2][(y - 1) * 2 + 1]= 1;
}
inline char get1(int x, int y) {
	return ans[(x - 1) * 2 + 1][y * 2] == 1 ? '-' : ' ';
}
inline char get2(int x, int y) {
	return ans[x * 2][(y - 1) * 2 + 1] == 1 ? '|' : ' ';
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++) {
		cin >> (tmps[i] + 1);
		for(int j= 1; j <= m; j++) {
			if(tmps[i][j] == 'T') v1[i].push_back(j), v2[j].push_back(i);
		}
	}
	for(int i= 1; i <= n; i++) {
		for(int j= 0; j < v1[i].size(); j+= 2) {
			int l= v1[i][j], r= v1[i][j + 1];
			for(int k= l; k < r; k++) set1(i, k);
		}
	}
	for(int i= 1; i <= m; i++) {
		for(int j= 0; j < v2[i].size(); j+= 2) {
			int l= v2[i][j], r= v2[i][j + 1];
			for(int k= l; k < r; k++) set2(k, i);
		}
	}
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) {
			putchar('o');
			putchar(get1(i, j));
		}
		putchar('\n');
        
		for(int j= 1; j <= m; j++) {
			putchar(get2(i, j));
			putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}