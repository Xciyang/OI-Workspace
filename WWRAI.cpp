/*
 * static Random random(time(0)) => a random
 * state.my => my_id
 * state.p => player_list
 * state.cnt => size of player_list
 * state.p[id].pos => player's pos (type: (struct)veci)
 * veci => struct{x, y, function operator + (veci), function len()}
 * btnstate["WASD"] => bool(down/up)
 * inMap(x, y) => judge pos
 * isWall(x, y) => judge wall
 * mouse_pos => mouse pos ???
 * lbtn => mouse down/up ???
 * MAP_SIZE_X 100
 * MAP_SIZE_Y 100
 * SIGHT_SIZE_X 31
 * SIGHT_SIZE_Y 21
 */

//---pre---

#define MAP_SIZE_X 100
#define MAP_SIZE_Y 100

#define SIGHT_SIZE_X 31
#define SIGHT_SIZE_Y 21

#include <vector>
#include <list>
#include <map>
#include <queue>
#include <cstring>
#include <ctime>
#include <cstdlib>
struct Random {
	Random(int) {
		return;
	}
};
template < typename T >
struct vec {
	int x, y;
};
typedef vec< int > veci;
typedef unsigned short uint16;
typedef long long int64;
struct PlayerState {
	char name[32];
	int flag_process;
	int procbar;
	int rest_bullet;
	veci pos;
	int health;
	int exstate;
	int weapon;
	bool remove;
	veci mouse_pos;
	bool button[256];
	int64 preupdate_move;
	int64 preupdate_shoot;
	bool lbtn, rbtn;
};
struct GameState {
	PlayerState p[50];
	std::list< Bullet > l_bt;
	uint16 my, cnt;
} state;
//---begin---

void CiyangAI() {
	static Random random(time(0));
	static struct AIState { int lastex, lastey; } ais;
	static struct CYNODE { int x, y, lastt; } nowno;
	int mx= state.p[state.my].pos.x, my= state.p[state.my].pos.y, nx, ny, clPlayer;
	double mindis= 1e9;
	std::vector< int > scPlayer;
	for(int i= 0; i < state.cnt; i++) {
		if(i == state.my || state.p[i].remove) continue;
		if(abs(state.p[i].pos.x - mx) * 2 <= SIGHT_SIZE_X * 1.5 && abs(state.p[i].pos.y - my) * 2 <= SIGHT_SIZE_Y * 1.5) scPlayer.push_back(i);
		if(mindis > (state.p[i].pos - state.p[state.my].pos).len()) mindis= (state.p[i].pos - state.p[state.my].pos).len(), clPlayer= i;
	}
	static int arBullet[MAP_SIZE_X][MAP_SIZE_Y], wp[MAP_SIZE_X][MAP_SIZE_Y];
	static int moves[][2]= {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
	static char movesc[][3]= {"AW", "AA", "AS", "WW", "SS", "DW", "DD", "DS"};
	memset(arBullet, 0, sizeof(arBullet));
	for(const auto &i : state.l_bt) {
		if(i.playerid == state.my) continue;
		vecd nowb= i.p;
		for(int j= 1; j <= i.base.move_pre_turn; j++) {
			nowb= NextPoint(nowb, i.e);
			if(!inMap((int)nowb.x, (int)nowb.y)) break;
			if(abs((int)nowb.x - mx) <= 3 && abs((int)nowb.y - my) <= 3) arBullet[(int)nowb.x][(int)nowb.y]= 1;
			if(isWall((int)nowb.x, (int)nowb.y) && !arBullet[(int)nowb.x][(int)nowb.y]) break;
		}
	}
	if(mindis > veci(SIGHT_SIZE_X, SIGHT_SIZE_Y).len()) lbtn= 0;
	btnstate['R']= btnstate['W']= btnstate['A']= btnstate['S']= btnstate['D']= 0;
	if(state.p[state.my].rest_bullet == 0) btnstate['R']= 1;
	if(scPlayer.size() == 0) {
		if(state.p[state.my].rest_bullet != GetPlayerWeapon(state.my).magazine) btnstate['R']= 1;
		std::queue< CYNODE > qu;
		int lsignt= max(0, mx - SIGHT_SIZE_X / 2 + 1), rsignt= min(mx + SIGHT_SIZE_X / 2, MAP_SIZE_X), usignt= max(0, my - SIGHT_SIZE_Y / 2 + 1), dsignt= min(my + SIGHT_SIZE_Y / 2, MAP_SIZE_Y);
		memset(wp, 0, sizeof(wp));
		for(int i= lsignt; i < rsignt; i++)
			for(int j= usignt; j < dsignt; j++)
				if(map_item[i][j]) {
					if(i == mx && j == my) return;
					qu.push(CYNODE{i, j, -1}), wp[i][j]= 1;
				}
		while(!qu.empty()) {
			nowno= qu.front(), qu.pop();
			if(nowno.x == mx && nowno.y == my) {
				for(int j= 0; j < 2; j++) btnstate[movesc[7 - nowno.lastt][j]]= 1;
				return;
			}
			for(int i= 0; i < 8; i++) {
				nx= nowno.x + moves[i][0], ny= nowno.y + moves[i][1];
				if(nx < lsignt || nx >= rsignt || ny < usignt || ny >= dsignt || wp[nx][ny]) continue;
				if(isWall(nx, my) || isWall(mx, ny) || isWall(nx, ny)) continue;
				qu.push(CYNODE{nx, ny, i}), wp[nx][ny]= 1;
			}
		}
		std::vector< int > canu;
		int flak= 0;
		for(int i= 0; i < 8; i++) {
			nx= mx + moves[i][0], ny= my + moves[i][1];
			if(!inMap(nx, ny) || isWall(nx, my) || isWall(mx, ny) || isWall(nx, ny)) continue;
			if(arBullet[nx][ny]) {
				flak= 1;
				continue;
			}
			canu.push_back(i);
		}
		if(!flak) {
			int cnt= 20;
			while(cnt--) {
				if(inMap(ais.lastex, ais.lastey) && !isWall(ais.lastex, ais.lastey) && !arBullet[ais.lastex][ais.lastey] && (ais.lastex != mx || ais.lastey != my)) break;
				ais.lastex+= random.rand() % 9 - 4, ais.lastey+= random.rand() % 9 - 4;
				ais.lastex= max(0, ais.lastex), ais.lastex= min(ais.lastex, MAP_SIZE_X - 1), ais.lastey= max(0, ais.lastey), ais.lastey= min(ais.lastey, MAP_SIZE_Y - 1);
			}
			if(inMap(ais.lastex, ais.lastey) && !isWall(ais.lastex, ais.lastey) && !arBullet[ais.lastex][ais.lastey] && (ais.lastex != mx || ais.lastey != my)) {
				std::queue< CYNODE > qu;
				qu.push(CYNODE{ais.lastex, ais.lastey, 0});
				memset(wp, 0, sizeof(wp)), wp[ais.lastex][ais.lastey]= 1;
				while(!qu.empty()) {
					nowno= qu.front(), qu.pop();
					if(nowno.x == mx && nowno.y == my) {
						flak= 1;
						for(int j= 0; j < 2; j++) btnstate[movesc[7 - nowno.lastt][j]]= 1;
						break;
					}
					for(int i= 0; i < 8; i++) {
						nx= nowno.x + moves[i][0], ny= nowno.y + moves[i][1];
						if(!inMap(nx, ny) || wp[nx][ny] || isWall(nx, ny)) continue;
						qu.push(CYNODE{nx, ny, i}), wp[nx][ny]= 1;
					}
				}
			}
		}
		if(!flak && !canu.empty()) {
			int num= random.rand() % canu.size();
			for(int j= 0; j < 2; j++) btnstate[movesc[canu[num]][j]]= 1;
		}
	}
	else if(scPlayer.size() == 1) {
		std::vector< int > canu;
		for(int i= 0; i < 8; i++) {
			nx= mx + moves[i][0], ny= my + moves[i][1];
			if(!inMap(nx, ny) || isWall(nx, my) || isWall(mx, ny) || isWall(nx, ny) || arBullet[nx][ny]) continue;
			canu.push_back(i);
		}
		if(canu.empty()) {
			for(int i= 0; i < 8; i++) {
				nx= mx + moves[i][0], ny= my + moves[i][1];
				if(!inMap(nx, ny) || isWall(nx, my) || isWall(mx, ny) || isWall(nx, ny)) continue;
				canu.push_back(i);
			}
		}
		if(!canu.empty()) {
			int num= random.rand() % canu.size();
			for(int j= 0; j < 2; j++) btnstate[movesc[canu[num]][j]]= 1;
		}
		if(mindis > veci(SIGHT_SIZE_X, SIGHT_SIZE_Y).len() / 3 && state.p[state.my].rest_bullet <= GetPlayerWeapon(state.my).magazine / 2 && romdom.rand() % 2) btnstate['R']= 1;
		mouse_pos= state.p[clPlayer].pos - state.p[state.my].pos + veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2), lbtn= 1;
	}
	else {
		int cnt= 20, falk= 0;
		while(cnt--) {
			if(inMap(ais.lastex, ais.lastey) && !isWall(ais.lastex, ais.lastey) && !arBullet[ais.lastex][ais.lastey] && (ais.lastex != mx || ais.lastey != my)) break;
			ais.lastex+= random.rand() % 9 - 4, ais.lastey+= random.rand() % 9 - 4;
			ais.lastex= max(0, ais.lastex), ais.lastex= min(ais.lastex, MAP_SIZE_X - 1), ais.lastey= max(0, ais.lastey), ais.lastey= min(ais.lastey, MAP_SIZE_Y - 1);
		}
		if(inMap(ais.lastex, ais.lastey) && !isWall(ais.lastex, ais.lastey) && !arBullet[ais.lastex][ais.lastey] && (ais.lastex != mx || ais.lastey != my)) {
			std::queue< CYNODE > qu;
			btnstate['W']= btnstate['A']= btnstate['S']= btnstate['D']= 0;
			memset(wp, 0, sizeof(wp)), wp[ais.lastex][ais.lastey]= 1;
			qu.push(CYNODE{ais.lastex, ais.lastey, 0});
			while(!qu.empty()) {
				nowno= qu.front(), qu.pop();
				if(nowno.x == mx && nowno.y == my) {
					falk= 1;
					for(int j= 0; j < 2; j++) btnstate[movesc[7 - nowno.lastt][j]]= 1;
					break;
				}
				for(int i= 0; i < 8; i++) {
					nx= nowno.x + moves[i][0], ny= nowno.y + moves[i][1];
					if(!inMap(nx, ny) || isWall(nx, ny) || wp[nx][ny]) continue;
					qu.push(CYNODE{nx, ny, i}), wp[nx][ny]= 1;
				}
			}
		}
		if(!falk) {
			for(int i= 0; i < 8; i++) {
				nx= mx + moves[i][0], ny= my + moves[i][1];
				if(!inMap(nx, ny) || isWall(nx, my) || isWall(mx, ny) || isWall(nx, ny)) continue;
				if(rand() % 4 == 0) {
					for(int j= 0; j < 2; j++) btnstate[movesc[i][j]]= 1;
					break;
				}
			}
		}
		mouse_pos= state.p[clPlayer].pos - state.p[state.my].pos + veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2), lbtn= 1;
	}
	return;
}