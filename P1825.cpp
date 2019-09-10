#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <map>
#include <queue>
using namespace std;
int n, m, bx, by, ex, ey;
char scene[400][400];
struct door {
    int x1, y1, x2, y2, open;
} tmpd;
map < char, door > doors;
inline void add(char c, int x, int y) {
    if(doors[c].open == 0) {
        doors[c].x1= x;
        doors[c].y1= y;
        doors[c].open= 1;
    }
    else if(doors[c].open == 1) {
        doors[c].x2= x;
        doors[c].y2= y;
        doors[c].open= 2;
    }
    return;
}
int walked[310][310], cnt;
int bfs() {
	queue < pair < pair < int , int > , int > > qu;
    register int posx, posy, nposx, nposy, step, moves[4][2]= {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
	qu.push(pair < pair < int , int > , int >(pair < int , int > (bx, by), 0));
	walked[bx][by]= 1;
	while(!qu.empty()) {
		posx= qu.front().first.first, posy= qu.front().first.second, step= qu.front().second, qu.pop();
        if(posx == ex && posy == ey) return step;
        for(int i= 0; i < 4; i++) {
            nposx= posx + moves[i][0], nposy= posy + moves[i][1];
            if(scene[nposx][nposy] == '#') continue;
			if(walked[nposx][nposy] && scene[nposx][nposy] == '.') continue;
			walked[nposx][nposy]= 1;
			if(scene[nposx][nposy] >= 'A' && scene[nposx][nposy] <= 'Z') {
                tmpd= doors[scene[nposx][nposy]];
                if(nposx == tmpd.x1 && nposy == tmpd.y1 && (tmpd.open == 2 || tmpd.open == 3)){
                	nposx= tmpd.x2, nposy= tmpd.y2;
                	if(tmpd.open == 2) tmpd.open = 4;
                	else tmpd.open = 5;
				} 
                else if(nposx == tmpd.x2 && nposy == tmpd.y2 && (tmpd.open == 2 || tmpd.open == 4)){
                	nposx= tmpd.x1, nposy= tmpd.y1;
					if(tmpd.open == 2) tmpd.open = 3;
                	else tmpd.open = 5;
				}
				walked[nposx][nposy]= 1;
            }
            qu.push(pair < pair < int , int > , int >(pair < int , int > (nposx, nposy), step + 1));
        }
    }
    return -1;
}
int main() {
    cin >> n >> m;
    for(int i= 0; i <= n + 1; i++) {
        for(int j= 0; j <= m + 1; j++) {
            if(i == 0 || i == n + 1 || j == 0 || j == m + 1) {
                scene[i][j]= '#';
                continue;
            }
            cin >> scene[i][j];
            if(scene[i][j] == '@') bx= i, by= j;
            if(scene[i][j] == '=') ex= i, ey= j;
            if(scene[i][j] >= 'A' && scene[i][j] <= 'Z') add(scene[i][j], i, j);
        }
    }
    cout << bfs() << endl;
    return 0;
}

