#include <iostream>
#include <stdio.h>
#include <map>
using namespace std;
int t, bx, by, k, flag[5][5];
struct GAMEST {
	int w[5][5];
	inline int operator<(const GAMEST &g2) const {
		int f3= 0;
		for(int i= 1; i <= 4; i++) {
			for(int j= 1; j <= 4; j++) {
				if(w[i][j] != g2.w[j][i]) f3= 1;
			}
		}
		for(int i= 1; i <= 4; i++) {
			for(int j= 1; j <= 4; j++) {
				if(w[i][j] != g2.w[i][j]) return w[i][j] < g2.w[i][j];
			}
		}
		return 0;
	}
} nown;
map< GAMEST, int > ms;
inline void clearflag() {
	for(int i= 1; i <= 4; i++)
		for(int j= 1; j <= 4; j++) flag[i][j]= 0;
}
inline int checkflag(int x) {
	int f2= 0;
	for(int i= 1; i <= 4; i++) {
		for(int j= 1; j <= 4; j++) {
			if(flag[i][j] && !nown.w[i][j]) {
				nown.w[i][j]= x;
				f2= 1;
			}
		}
	}
	return f2;
}
int left(int x) {
	clearflag();
	int f= 0;
	for(int j= 2; j <= 4; j++) {
		for(int i= 1; i <= 4; i++) {
			if(nown.w[i][j]) {
				int x= j;
				while(x > 1 && !nown.w[i][x - 1]) nown.w[i][x - 1]= nown.w[i][x], nown.w[i][x]= 0, --x;
				if(x > 1 && nown.w[i][x - 1] == nown.w[i][x]) nown.w[i][x - 1]+= nown.w[i][x], nown.w[i][x]= 0, --x, f+= nown.w[i][x];
				if(x != j) flag[i][j]= 1;
			}
		}
	}
	int f2= checkflag(x);
	return f ? f : (f2 ? 0 : -1);
}
int right(int x) {
	clearflag();
	int f= 0;
	for(int j= 3; j >= 1; j--) {
		for(int i= 1; i <= 4; i++) {
			if(nown.w[i][j]) {
				int x= j;
				while(x < 4 && !nown.w[i][x + 1]) nown.w[i][x + 1]= nown.w[i][x], nown.w[i][x]= 0, ++x;
				if(x < 4 && nown.w[i][x + 1] == nown.w[i][x]) nown.w[i][x + 1]+= nown.w[i][x], nown.w[i][x]= 0, ++x, f+= nown.w[i][x];
				if(x != j) flag[i][j]= 1;
			}
		}
	}
	int f2= checkflag(x);
	return f ? f : (f2 ? 0 : -1);
}
int up(int x) {
	clearflag();
	int f= 0;
	for(int i= 2; i <= 4; i++) {
		for(int j= 1; j <= 4; j++) {
			if(nown.w[i][j]) {
				int x= i;
				while(x > 1 && !nown.w[x - 1][j]) nown.w[x - 1][j]= nown.w[x][j], nown.w[x][j]= 0, --x;
				if(x > 1 && nown.w[x - 1][j] == nown.w[x][j]) nown.w[x - 1][j]+= nown.w[x][j], nown.w[x][j]= 0, --x, f+= nown.w[x][j];
				if(x != j) flag[i][j]= 1;
			}
		}
	}
	int f2= checkflag(x);
	return f ? f : (f2 ? 0 : -1);
}
int down(int x) {
	clearflag();
	int f= 0;
	for(int i= 3; i >= 1; i--) {
		for(int j= 1; j <= 4; j++) {
			if(nown.w[i][j]) {
				int x= i;
				while(x < 4 && !nown.w[x + 1][j]) nown.w[x + 1][j]= nown.w[x][j], nown.w[x][j]= 0, ++x;
				if(x < 4 && nown.w[x + 1][j] == nown.w[x][j]) nown.w[x + 1][j]+= nown.w[x][j], nown.w[x][j]= 0, ++x, f+= nown.w[x][j];
				if(x != j) flag[i][j]= 1;
			}
		}
	}
	int f2= checkflag(x);
	return f ? f : (f2 ? 0 : -1);
}
int dfs(int x, int sc) {
	if(ms[nown] >= sc) return 0;
	ms[nown]= sc;
	// for(int i= 1; i <= 4; i++) {
	// 	for(int j= 1; j <= 4; j++) {
	// 		cout << nown.w[i][j] << ' ';
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;
	if(sc >= k) {
		cout << "YES" << endl;
		return 1;
	}
	int res;
	GAMEST s= nown;
	res= left((x + 1) * 2);
	if(res != -1) {
		if(dfs(x ^ 1, sc + res)) return 1;
	}
	nown= s, res= right((x + 1) * 2);
	if(res != -1) {
		if(dfs(x ^ 1, sc + res)) return 1;
	}
	nown= s, res= up((x + 1) * 2);
	if(res != -1) {
		if(dfs(x ^ 1, sc + res)) return 1;
	}
	nown= s, res= down((x + 1) * 2);
	if(res != -1) {
		if(dfs(x ^ 1, sc + res)) return 1;
	}
	return 0;
}
int main() {
	cin >> t;
	while(t--) {
		cin >> k;
		cin >> bx >> by;
		for(int i= 1; i <= 4; i++)
			for(int j= 1; j <= 4; j++) nown.w[i][j]= 0;
		nown.w[bx][by]= 2;
		dfs(0, 2);
	}
	return 0;
}
/*
5
500000
3 3
*/