#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
int r, c, ans= -1;
int walkpast[35][35][35][35], bx[2], by[2], ex, ey;
char inmap[35][35];
struct NODE {
	int x1, y1, x2, y2, step;
};
queue< NODE > qu;
int moves[4][4]= {{-1, 0, -1, 0}, {0, -1, 0, 1}, {0, 1, 0, -1}, {1, 0, 1, 0}};
int main() {
	cin >> r >> c;
	for(int i= 1; i <= r; i++) {
		for(int j= 1; j <= c; j++) {
			cin >> inmap[i][j];
			if(inmap[i][j] == 'G') {
				inmap[i][j]= '.';
				bx[0]= i, by[0]= j;
			}
			if(inmap[i][j] == 'M') {
				inmap[i][j]= '.';
				bx[1]= i, by[1]= j;
			}
			if(inmap[i][j] == 'T') {
				inmap[i][j]= '.';
				ex= i, ey= j;
			}
		}
	}
	walkpast[bx[0]][by[0]][bx[1]][by[1]]= 1;
	qu.push(NODE{bx[0], by[0], bx[1], by[1], 0});
	register NODE qf, nf;
	while(!qu.empty()) {
		qf= qu.front(), qu.pop();
		if(qf.x1 == ex && qf.y1 == ey && qf.x2 == ex && qf.y2 == ey) {
			ans= qf.step;
			break;
		}
		for(int i= 0; i < 4; i++) {
			nf.x1= qf.x1 + moves[i][0], nf.y1= qf.y1 + moves[i][1];
			if(inmap[nf.x1][nf.y1] == '#') nf.x1= qf.x1, nf.y1= qf.y1;
			if(inmap[nf.x1][nf.y1] == 'X') continue;
			nf.x2= qf.x2 + moves[i][2], nf.y2= qf.y2 + moves[i][3];
			if(inmap[nf.x2][nf.y2] == '#') nf.x2= qf.x2, nf.y2= qf.y2;
			if(inmap[nf.x2][nf.y2] == 'X') continue;
			if(walkpast[nf.x1][nf.y1][nf.x2][nf.y2]) continue;
			nf.step= qf.step + 1;
			walkpast[nf.x1][nf.y1][nf.x2][nf.y2]= 1, qu.push(nf);
		}
	}
	if(ans == -1)
		cout << "no" << endl;
	else
		cout << ans << endl;
	return 0;
}