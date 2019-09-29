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
void Game::CiyangAI() {
	// return;
	static Random random(time(0));
	static struct AIState { int lastex, lastey; } ais= {state.p[state.my].pos.x, state.p[state.my].pos.y};
	static struct CYNODE { int x, y, lastt; } nowno;
	int mx= state.p[state.my].pos.x, my= state.p[state.my].pos.y, nx, ny, lastab, flak= 0, clPlayer;
	double mindis= 1e9;
	std::vector< int > scPlayer;
	for(int i= 0; i < state.cnt; i++) {
		if(i == state.my || state.p[i].remove) continue;
		if(abs(state.p[i].pos.x - mx) <= SIGHT_SIZE_X * 1.5 && abs(state.p[i].pos.y - my) <= SIGHT_SIZE_Y * 1.5) scPlayer.push_back(i);
		if(mindis > (state.p[i].pos - state.p[state.my].pos).len()) mindis= (state.p[i].pos - state.p[state.my].pos).len(), clPlayer= i;
	}
	static int arBullet[MAP_SIZE_X][MAP_SIZE_Y], wp[MAP_SIZE_X][MAP_SIZE_Y], moves[][2]= {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
	static char movesc[][3]= {"AW", "AA", "AS", "WW", "SS", "DW", "DD", "DS"};
	auto RandNextPos= [mx, my, this](int cnt) -> void {
		while(cnt--) {
			if(inMap(ais.lastex, ais.lastey) && !isWall(ais.lastex, ais.lastey) && (abs(ais.lastex - mx) + abs(ais.lastey - my)) > 4) break;
			ais.lastex+= random.rand() % 30 - 15, ais.lastey+= random.rand() % 30 - 15;
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

	auto BFSRandPos= [this, RandNextPos, BFSNextPos, mx, my, &flak]() -> int {
		RandNextPos(20);
		if(inMap(ais.lastex, ais.lastey) && !isWall(ais.lastex, ais.lastey) && !arBullet[ais.lastex][ais.lastey] && (ais.lastex != mx || ais.lastey != my)) {
			std::queue< CYNODE > qu;
			qu.push(CYNODE{ais.lastex, ais.lastey, 0});
			memset(wp, 0, sizeof(wp)), wp[ais.lastex][ais.lastey]= 1;
			int res= BFSNextPos(qu, 1);
			if(res < 8) {
				btnstate['W']= btnstate['A']= btnstate['S']= btnstate['D']= 0;
				for(int j= 0; j < 2; j++) btnstate[movesc[res][j]]= 1;
				flak= 1;
			}
			if(res == 8) RandNextPos(2);
		}
		return 0;
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
	if(lbtn && random.rand() % 2) lbtn= 0;
	if(state.p[state.my].flag_process == PT_RELOAD) btnstate['R']= 0;
	if(state.p[state.my].flag_process != PT_RELOAD && (state.p[state.my].rest_bullet == 0 || (mindis + 1 > GetPlayerWeapon(state.my).reload_time / 5 && state.p[state.my].rest_bullet < 5))) btnstate['R']= 1;
	if(state.p[state.my].flag_process == PT_RELOAD || scPlayer.size() <= 1) {
		memset(wp, 0, sizeof(wp));
		std::queue< CYNODE > qu;
		for(int i= 0; i < MAP_SIZE_X; i++)
			for(int j= 0; j < MAP_SIZE_Y; j++)
				if(map_item[i][j] && !arBullet[i][j]) qu.push(CYNODE{i, j, -1}), wp[i][j]= 1;
		int res= BFSNextPos(qu, 1);
		if(res < 8) {
			btnstate['W']= btnstate['A']= btnstate['S']= btnstate['D']= 0;
			for(int j= 0; j < 2; j++) btnstate[movesc[res][j]]= 1;
			flak= 1;
		}
	}
	if(scPlayer.size() == 0) {
		if(!flak) BFSRandPos();
	}
	else if(scPlayer.size() == 1) {
		veci lastm= mouse_pos;
		if(!lbtn) lbtn= 1, flak= 1;
		if(random.rand() % 2 == 0) flak= 1, mouse_pos= state.p[clPlayer].pos - state.p[state.my].pos + veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2) + veci(random.rand() % 2 - 1, random.rand() % 2 - 1);
		for(vecd bp= state.p[state.my].pos, bv= getv(state.p[state.my].pos, state.p[state.my].pos + (mouse_pos - veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2))); (bp - state.p[state.my].pos).len() < mindis && inMap(roundx(bp.x), roundx(bp.y));
			bp= bp + bv) {
			if(isWall(roundx(bp.x), roundx(bp.y)) && random.rand() % 3 == 0) {
				lbtn= 0, mouse_pos= lastm, flak= 0;
				break;
			}
		}
		if(!flak || random.rand() % 5 == 0) BFSRandPos();
	}
	else {
		if(lbtn && random.rand() % 2) mouse_pos= state.p[clPlayer].pos - state.p[state.my].pos + veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2) + veci(random.rand() % 2 - 1, random.rand() % 2 - 1);
		if(random.rand() % 2 && !lbtn) lbtn= 1, flak= 1;
		if(!flak || random.rand() % 10 == 0) BFSRandPos();
	}
	return;
}