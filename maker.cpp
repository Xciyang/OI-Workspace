#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;
#define BLOCK_AIR 0
#define BLOCK_DIRT 1
#define BLOCK_STONE 2
int room[20][20];
int moves[8][2]= {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
int moves2[4][2]= {{-1,0},{0,-1},{0,1},{1,0}};
inline int limited(int x, int y) {
	return x < 0 || y < 0 || x > 19 || y > 19;
}
vector < int > qx, qy;
int main() {
	srand(time(0));
	for(int i= 0; i < 20; i++) for(int j= 0 ; j < 20; j++) room[i][j]= 9;
	for(int i= 0; i < 15; i++) {
		int x= rand() % 20, y= rand() % 20;
		room[x][y] = rand() % 3 ? 0 : 1 + rand() % 2;
		qx.push_back(x), qy.push_back(y);
	}
making:
	for(int i= 0; i < 10; i++) {
		int xx= rand() % qx.size(), yy= rand() % qy.size();
		int x= qx[xx], y= qy[yy];
		for(int j= 0; j < 8; j++) {
			int nx = x + moves[j][0], ny = y + moves[j][1];
			if(!limited(nx, ny) && room[nx][ny] == 9) {
				room[nx][ny]= room[x][y];
				qx.push_back(nx), qy.push_back(ny);
			}
		}
		qx.erase(qx.begin() + xx), qy.erase(qy.begin() + yy);
	}
	for(int i= 0; i < 20; i++) {
		for(int j= 0; j < 20; j++) {
			if(room[i][j] == 9) {
				room[i][j]= rand() % 3 ? 0 : 1 + rand() % 2;
				qx.push_back(i), qy.push_back(j);
				goto making;
			}
		}
	}
	for(int i= 0; i < 20; i++) {
		for(int j= 0; j < 20; j++) {
			if(room[i][j] == 0) {
				for(int k= 0; k < 4; k++) {
					int x= i + moves2[k][0], y= j + moves2[k][1];
					if(limited(x, y)) continue;
					if(!room[x][y]) goto nxt;
				}
				room[i][j]= 1 + rand() % 2;
				nxt:;
			}
		}
	}
	for(int i= 0; i < 20; i++, printf("\n")) for(int j= 0 ; j < 20; j++) printf("%d ", room[i][j]);
	freopen("a.out", "w", stdout);
	printf("[");
	for(int i= 0; i < 20; i++) {
		printf("[");
		for(int j= 0; j < 20; j++) {
			printf("%d", room[i][j]);
			if(j != 19) printf(",");
		}
		printf("]");
		if(i != 19) printf(",");
	}
	printf("]");
	return 0;
}
