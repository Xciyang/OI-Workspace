#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;

const int maxk= 50;
const int maxNM= 40;

int k, n, m, cnt;
char mj[maxk][4][4], endm[maxNM][maxNM];
int qc(int nown) {
	for(int i= 1; i < nown; i++) {
		for(int j= 1; j <= 3; j++) {
			for(int l= 1; l <= 3; l++) {
				if(mj[nown][j][l] != mj[i][j][l]) goto nextt;
			}
		}
		return 1;
	nextt:;
	}
	return 0;
}
void makemj() {
	for(int i= 1; i <= k; i++) {
		cnt= 0;
		for(int j= 1; j <= 3; j++) {
			for(int l= 1; l <= 3; l++) {
				if(j == 1 && l == 1)
					mj[i][j][l]= '*';
				else if(rand() % 2)
					mj[i][j][l]= '*', ++cnt;
				else
					mj[i][j][l]= '#';
			}
		}
		if(cnt < 3 || cnt > 6 || qc(i)) --i;
	}
}
void makem() {
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) {
			if(!endm[i][j]) {
			retry:
				if(rand() % 10 == 0) {
					int tmpx= rand() % k + 1;
					for(int x= 1; x <= 3; x++) {
						for(int y= 1; y <= 3; y++) {
							if(mj[tmpx][x][y] == '*' && (endm[i + x - 1][j + y - 1] == '*' || i + x > n || j + y > m)) goto retry;
						}
					}
					for(int x= 1; x <= 3; x++) {
						for(int y= 1; y <= 3; y++) {
							if(mj[tmpx][x][y] == '*') endm[i + x - 1][j + y - 1]= '*';
						}
					}
				}
				else
					endm[i][j]= '#';
			}
		}
	}
}
int main() {
	srand(time(0));
	freopen("./PGM/make.txt", "w", stdout);
	k= 10, n= 34, m= 36;
	cout << k << ' ' << n << ' ' << m << endl;
	makemj(), makem();
	for(int i= 1; i <= k; i++) {
		for(int j= 1; j <= 3; j++) {
			for(int l= 1; l <= 3; l++) putchar(mj[i][j][l]);
			putchar('\n');
		}
	}
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) {
			putchar(endm[i][j]);
		}
		putchar('\n');
	}
	return 0;
}