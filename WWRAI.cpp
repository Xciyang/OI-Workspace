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

#include <vector>
#include <list>
#include <map>
#include <queue>
#include <cstring>
#include <ctime>
#include <cstdlib>

//---begin---
void CiyangAI() {
	// return;
	static Random random(time(0));
	static struct AIState { int lastex, lastey; } ais;
	static struct CYNODE { int x, y, lastt; } nowno;
	int mx= state.p[state.my].pos.x, my= state.p[state.my].pos.y, nx, ny, clPlayer, lastab, flak= 0;
	double mindis= 1e9;
	std::vector< int > scPlayer;
	for(int i= 0; i < state.cnt; i++) {
		if(i == state.my || state.p[i].remove) continue;
		if(abs(state.p[i].pos.x - mx) * 2 <= SIGHT_SIZE_X * 1.5 && abs(state.p[i].pos.y - my) * 2 <= SIGHT_SIZE_Y * 1.5) scPlayer.push_back(i);
		if(mindis > (state.p[i].pos - state.p[state.my].pos).len()) mindis= (state.p[i].pos - state.p[state.my].pos).len(), clPlayer= i;
	}
	static int arBullet[MAP_SIZE_X][MAP_SIZE_Y], wp[MAP_SIZE_X][MAP_SIZE_Y], moves[][2]= {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
	static char movesc[][3]= {"AW", "AA", "AS", "WW", "SS", "DW", "DD", "DS"};
	auto RandNextPos= [mx, my, this](int cnt) -> void {
		while(cnt--) {
			if(inMap(ais.lastex, ais.lastey) && !isWall(ais.lastex, ais.lastey) && !arBullet[ais.lastex][ais.lastey] && (ais.lastex != mx || ais.lastey != my)) break;
			ais.lastex+= random.rand() % 9 - 4, ais.lastey+= random.rand() % 9 - 4;
			ais.lastex= max(0, ais.lastex), ais.lastex= min(ais.lastex, MAP_SIZE_X - 1), ais.lastey= max(0, ais.lastey), ais.lastey= min(ais.lastey, MAP_SIZE_Y - 1);
		}
		return;
	};
	auto BFSNextPos= [mx, my, &nx, &ny, this](std::queue< CYNODE > &qu, int bul) -> int {
		while(!qu.empty()) {
			nowno= qu.front(), qu.pop();
			if(nowno.x == mx && nowno.y == my) return 7 - nowno.lastt;
			for(int i= 0; i < 8; i++) {
				nx= nowno.x + moves[i][0], ny= nowno.y + moves[i][1];
				if(!inMap(nx, ny) || isWall(nx, ny) || wp[nx][ny]) continue;
				if(bul && arBullet[nx][ny]) continue;
				qu.push(CYNODE{nx, ny, i}), wp[nx][ny]= 1;
			}
		}
		return 8;
	};
	auto NormalNextPos= [mx, my, &nx, &ny, this](std::vector< int > &canu, std::vector< int > &canuu) -> void {
		for(int i= 0; i < 8; i++) {
			nx= mx + moves[i][0], ny= my + moves[i][1];
			if(!inMap(nx, ny) || isWall(nx, my) || isWall(mx, ny) || isWall(nx, ny)) continue;
			canuu.push_back(i);
			if(arBullet[nx][ny]) continue;
			canu.push_back(i);
		}
		return;
	};
	memset(arBullet, 0, sizeof(arBullet));
	for(const auto &i : state.l_bt) {
		if(i.playerid == state.my) continue;
		vecd nowb= i.p;
		for(int j= 1; j <= i.base.move_pre_turn; j++) {
			nowb= nowb + i.v;
			if(!inMap(roundx(nowb.x), roundx(nowb.y))) break;
			lastab= arBullet[roundx(nowb.x)][roundx(nowb.y)], arBullet[roundx(nowb.x)][roundx(nowb.y)]= 1;
			if(isWall(roundx(nowb.x), roundx(nowb.y)) && !lastab) break;
		}
	}
	lbtn= btnstate['R']= btnstate['W']= btnstate['A']= btnstate['S']= btnstate['D']= 0;
	if(state.p[state.my].rest_bullet == 0) btnstate['R']= 1;
	if(scPlayer.size() == 0) {
		if(state.p[state.my].rest_bullet != GetPlayerWeapon(state.my).magazine) {
			if(mindis > GetPlayerWeapon(state.my).reload_time / 5 && state.p[state.my].rest_bullet < 20) btnstate['R']= 1;
			memset(wp, 0, sizeof(wp));
			std::queue< CYNODE > qu;
			for(int i= 0; i < SIGHT_SIZE_X; i++)
				for(int j= 0; j < SIGHT_SIZE_Y; j++)
					if(map_item[i][j] && !arBullet[i][j]) {
						if(i == mx && j == my) return;
						qu.push(CYNODE{i, j, -1}), wp[i][j]= 1;
					}
			int res= BFSNextPos(qu, 1);
			if(res < 8) {
				for(int j= 0; j < 2; j++) btnstate[movesc[res][j]]= 1;
				flak= 1;
			}
		}
		if(!flak) {
			RandNextPos(20);
			if(inMap(ais.lastex, ais.lastey) && !isWall(ais.lastex, ais.lastey) && !arBullet[ais.lastex][ais.lastey] && (ais.lastex != mx || ais.lastey != my)) {
				std::queue< CYNODE > qu;
				qu.push(CYNODE{ais.lastex, ais.lastey, 0});
				memset(wp, 0, sizeof(wp)), wp[ais.lastex][ais.lastey]= 1;
				int res= BFSNextPos(qu, 1);
				if(res < 8) {
					for(int j= 0; j < 2; j++) btnstate[movesc[res][j]]= 1;
					flak= 1;
				}
			}
		}
		if(!flak) {
			std::vector< int > canu, canuu;
			NormalNextPos(canu, canuu);
			if(!canu.empty()) {
				int num= random.rand() % canu.size();
				for(int j= 0; j < 2; j++) btnstate[movesc[canu[num]][j]]= 1;
				flak= 1;
			}
		}
	}
	else if(scPlayer.size() == 1) {
		ais.lastex= mx, ais.lastey= my;
		RandNextPos(20);
		if(inMap(ais.lastex, ais.lastey) && !isWall(ais.lastex, ais.lastey) && !arBullet[ais.lastex][ais.lastey] && (ais.lastex != mx || ais.lastey != my)) {
			std::queue< CYNODE > qu;
			qu.push(CYNODE{ais.lastex, ais.lastey, 0});
			memset(wp, 0, sizeof(wp)), wp[ais.lastex][ais.lastey]= 1;
			int res= BFSNextPos(qu, 1);
			if(res < 8) {
				for(int j= 0; j < 2; j++) btnstate[movesc[res][j]]= 1;
				flak= 1;
			}
		}
		if(!flak) {
			std::vector< int > canu, canuu;
			NormalNextPos(canu, canuu);
			if(canu.empty()) canu= canuu;
			if(!canu.empty()) {
				int num= random.rand() % canu.size();
				for(int j= 0; j < 2; j++) btnstate[movesc[canu[num]][j]]= 1;
				flak= 1;
			}
		}
		if(mindis > GetPlayerWeapon(state.my).reload_time / 5 && random.rand() % 2) btnstate['R']= 1;
		mouse_pos= state.p[clPlayer].pos - state.p[state.my].pos + veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2), lbtn= 1;
		for(vecd bp= state.p[state.my].pos, bv= getv(state.p[state.my].pos, state.p[state.my].pos + (mouse_pos - veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2))); (bp - state.p[state.my].pos).len() < mindis && inMap(roundx(bp.x), roundx(bp.y));
			bp= bp + bv) {
			if(isWall(roundx(bp.x), roundx(bp.y)) && !lastab) {
				if(rand() % 2) {
					lbtn= 0;
					break;
				}
			}
		}
	}
	else {
		std::vector< int > canu, canuu;
		NormalNextPos(canu, canuu);
		if(!canu.empty()) {
			int num= random.rand() % canu.size();
			for(int j= 0; j < 2; j++) btnstate[movesc[canu[num]][j]]= 1;
			flak= 1;
		}
		if(!flak) {
			RandNextPos(20);
			if(inMap(ais.lastex, ais.lastey) && !isWall(ais.lastex, ais.lastey) && !arBullet[ais.lastex][ais.lastey] && (ais.lastex != mx || ais.lastey != my)) {
				std::queue< CYNODE > qu;
				memset(wp, 0, sizeof(wp)), wp[ais.lastex][ais.lastey]= 1;
				qu.push(CYNODE{ais.lastex, ais.lastey, 0});
				int res= BFSNextPos(qu, 0);
				if(res < 8) {
					for(int j= 0; j < 2; j++) btnstate[movesc[res][j]]= 1;
					flak= 1;
				}
			}
		}
		if(!flak) {
			if(canu.empty()) canu= canuu;
			if(!canu.empty()) {
				int num= random.rand() % canu.size();
				for(int j= 0; j < 2; j++) btnstate[movesc[canu[num]][j]]= 1;
			}
			flak= 1;
		}
		mouse_pos= state.p[clPlayer].pos - state.p[state.my].pos + veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2), lbtn= 1;
	}
	return;
}