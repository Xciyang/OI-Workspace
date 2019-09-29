#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
using namespace std;
int n, nowp, len, ans;
char tmps[400005];
/*
1
.*#.#*......*#.**
*/
int main() {
	cin >> n;
	while(n--) {
		cin >> (tmps + 1), len= strlen(tmps + 1), ans= nowp= 0;
		while(len && tmps[len] == '#') tmps[len--]= 0;
		int i;
		for(i= 1; i <= len; i++) {
			if(tmps[i] == '*') ++nowp, tmps[i]= '.';
			ans= max(ans, nowp);
			if(i + 1 <= len && tmps[i + 1] == '#') {
				if(tmps[i] == '#' && tmps[i + 2] != '*') break;
				else if(tmps[i] == '.' && tmps[i + 2] != '*') {
					if(!nowp) break;
					--nowp, tmps[i]= '*';
				}
			}
			if(i - 1 >= 1 && tmps[i - 1] == '#' && tmps[i] == '.') {
				if(i - 2 >= 1 && tmps[i - 2] == '*') {
					if(nowp) ++nowp, tmps[i - 2]= '.';
				}
			}
			ans= max(ans, nowp);
		}
		if(i > len) i= len;
		for(; i; i--) {
			if(tmps[i] == '*') ++nowp, tmps[i]= '.';
			ans= max(ans, nowp);
			if(i - 1 >= 1 && tmps[i - 1] == '#') {
				if(!(i - 2 >= 1 && tmps[i - 2] == '*')) --nowp, tmps[i]= '*';
			}
			if(i + 1 <= len && tmps[i] == '.' && tmps[i + 1] == '#') {
				if(i + 2 <= len && tmps[i + 2] == '*') {
					if(nowp) ++nowp, tmps[i + 2]= '.';
				}
			}
			ans= max(ans, nowp);
		}
		cout << ans << endl;
	}

	return 0;
}
/*
1
.*#*#....*##*..
3

1
...*#..#**#.*
4

1
...*#*#*...##*...##...
3
*/