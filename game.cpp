#include "game.h"
// vecd NextPoint(vecd s, vecd e) {
//	vecd ret;
//	double cnt = max(abs(s.x - e.x), abs(s.y - e.y));
//	ret.x = s.x + (s.x - e.x) / cnt;
//	ret.y = s.y + (s.y - e.y) / cnt;
//	return ret;
//}
inline int roundx(double v) {
	return v > 0.0 ? v + 0.5 : v - 0.5;
}
inline vecd getv(vecd s, vecd e) {
	return vecd(e.x - s.x, e.y - s.y) / max(abs(e.x - s.x), abs(e.y - s.y));
}
void SetConsoleSize(int X, int Y) {
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.dwSize= 1;
	curInfo.bVisible= FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	SMALL_RECT rect;
	rect.Left= 1;
	rect.Top= 1;
	rect.Right= X * 2;
	rect.Bottom= Y + 1;
	// int e = SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &rect);
	CONSOLE_SCREEN_BUFFER_INFO info;
	UNEXCEPT_DO(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info));
	int w= info.srWindow.Right - info.srWindow.Left + 1;
	int h= info.srWindow.Bottom - info.srWindow.Top + 1;
	COORD siz;
	siz.X= max(rect.Right - rect.Left + 1, w);
	siz.Y= max(rect.Bottom - rect.Top + 1, h);
	UNEXCEPT_DO(SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), siz));
	UNEXCEPT_DO(SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &rect));
	siz.X= rect.Right - rect.Left + 1;
	siz.Y= rect.Bottom - rect.Top + 1;
	UNEXCEPT_DO(SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), siz));
}

bool Game::inMap(int x, int y) {
	return x >= 0 && y >= 0 && x < MAP_SIZE_X && y < MAP_SIZE_Y;
}
bool Game::inMap(const veci &p) {
	return inMap(p.x, p.y);
}
bool Game::isWall(int x, int y) {
	return map_wall[y][x].health > 0;
}
bool Game::isWall(const veci &p) {
	return isWall(p.x, p.y);
}
const Weapon &Game::GetPlayerWeapon(int x) {
	return v_weapon[state.p[x].weapon];
}
//#ifdef GAME_AI
void Game::CiyangAI() {
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
	auto judgeBTN= [this](char w, int c) -> bool { return c == btnstate[w]; };
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
	if(state.p[i].flag_process == PT_RELOAD) btnstate['R']= 0;
	if(state.p[state.my].flag_process != PT_RELOAD && mindis > GetPlayerWeapon(state.my).reload_time / 5 && state.p[state.my].rest_bullet < 10) btnstate['R']= 1;
	if(scPlayer.size() == 0) {
		if(state.p[state.my].rest_bullet != GetPlayerWeapon(state.my).magazine) {
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
				btnstate['W']= btnstate['A']= btnstate['S']= btnstate['D']= 0;
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
	}
	else if(scPlayer.size() == 1) {
		flak= 1;
		veci lastm= mouse_pos;
		mouse_pos= state.p[clPlayer].pos - state.p[state.my].pos + veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2), lbtn= 1;
		for(vecd bp= state.p[state.my].pos, bv= getv(state.p[state.my].pos, state.p[state.my].pos + (mouse_pos - veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2))); (bp - state.p[state.my].pos).len() < mindis && inMap(roundx(bp.x), roundx(bp.y));
			bp= bp + bv) {
			if(isWall(roundx(bp.x), roundx(bp.y)) && random.rand() % 2) {
				lbtn= 0, mouse_pos= lastm, flak= 0;
				break;
			}
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
	}
	else {
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
		if(lbtn && random.rand() % 2) mouse_pos= state.p[clPlayer].pos - state.p[state.my].pos + veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2), lbtn= 1;
	}
	return;
}
//#endif
#ifndef GAME_AI
void Game::UpdateConsole() {
	static wchar_t buffer[SIGHT_SIZE_Y + 1][SIGHT_SIZE_X + STATEBAR_SIZE_X * 2];

	static int p= 0;
	p= (p + 1) & 1;

	int y= state.p[state.my].pos.y - SIGHT_SIZE_Y / 2;
	int x= state.p[state.my].pos.x - SIGHT_SIZE_X / 2;
	for(int i= 0; i < SIGHT_SIZE_Y; i++) {
		for(int j= 0; j < SIGHT_SIZE_X; j++) {
			int px= j + x, py= i + y;
			if(px >= 0 && px < MAP_SIZE_X && py >= 0 && py < MAP_SIZE_Y)
				buffer[i][j]= map_buff[py][px];
			else
				buffer[i][j]= L'��';  // �ˡ�
		}
	}

	for(int i= 0; i < SIGHT_SIZE_Y; i++) {
		for(int j= SIGHT_SIZE_X; j < SIGHT_SIZE_X + STATEBAR_SIZE_X; j++) {
			buffer[i][j]= L'��';  // �ˡ�
		}
	}
	for(int i= 0; i < SIGHT_SIZE_Y; i++) {
		buffer[i][SIGHT_SIZE_X + 1]= L'|';
	}
	swprintf(&buffer[0][SIGHT_SIZE_X + 2], L"weapon:%hs", GetPlayerWeapon(state.my).name.c_str());
	swprintf(&buffer[1][SIGHT_SIZE_X + 2], L"magazine:%d/%d", state.p[state.my].rest_bullet, GetPlayerWeapon(state.my).magazine);
	swprintf(&buffer[2][SIGHT_SIZE_X + 2], L"timer:%d", state.p[state.my].procbar);
	swprintf(&buffer[3][SIGHT_SIZE_X + 2], L"rest:%d", GetAlivePlayerCnt());

	int health_bar= SIGHT_SIZE_X * state.p[state.my].health / 100;
	for(int i= 0; i < SIGHT_SIZE_X; i++) buffer[SIGHT_SIZE_Y][i]= i < health_bar ? L'��' : L'��';
	for(int i= 0; i < SIGHT_SIZE_Y + 1; i++) {
		DWORD dw;
		WriteConsoleOutputCharacter(hconbuf[p], (LPCWSTR)buffer[i], SIGHT_SIZE_X + STATEBAR_SIZE_X, COORD{(SHORT)0, (SHORT)i}, &dw);
	}
	SetConsoleActiveScreenBuffer(hconbuf[p]);
	hconnow= hconbuf[p];
}
void Game::DrawConsoleBuffer() {
	for(int i= 0; i < MAP_SIZE_Y; i++)
		for(int j= 0; j < MAP_SIZE_X; j++) map_buff[i][j]= L'��';

	for(int i= 0; i < MAP_SIZE_Y; i++)
		for(int j= 0; j < MAP_SIZE_X; j++)
			if(map_item[i][j] != 0) {
				switch(map_item[i][j]) {
					case IT_RANDWEAPEN:
						map_buff[i][j]= L'�d';
						// case IT_HEAL:map_buff[i][j] = L'�d';
				}
			}

	for(const auto &b : state.l_bt) {
		if(inMap(b.p)) map_buff[roundx(b.p.y)][roundx(b.p.x)]= L'��';
	}

	for(int i= 0; i < state.cnt; i++) {
		if(state.p[i].remove) continue;
		int px= state.p[i].pos.x, py= state.p[i].pos.y;
		map_buff[py][px]= L'��';
		wchar_t wc= L'��';
		vecd vertical(0, -1);
		vecd v= state.p[i].mouse_pos - vecd(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2);
		//���J���K�����L�I
		double cosx= vertical * v / vertical.len() / v.len();
		double a= acos(vertical * v / vertical.len() / v.len()) * 180 / PI;
		if((vertical ^ v) > 0) {
			if(a <= 22.5) {
				if(inMap(veci(py - 1, px))) map_buff[py - 1][px]= L'��';
			}
			else if(a <= 67.5) {
				if(inMap(veci(py - 1, px + 1))) map_buff[py - 1][px + 1]= L'�J';
			}
			else if(a <= 112.5) {
				if(inMap(veci(py, px + 1))) map_buff[py][px + 1]= L'��';
			}
			else if(a <= 157.5) {
				if(inMap(veci(py + 1, px + 1))) map_buff[py + 1][px + 1]= L'�K';
			}
			else {
				if(inMap(veci(py + 1, px))) map_buff[py + 1][px]= L'��';
			}
		}
		else {
			if(a <= 22.5) {
				if(inMap(veci(py - 1, px))) map_buff[py - 1][px]= L'��';
			}
			else if(a <= 67.5) {
				if(inMap(veci(py - 1, px - 1))) map_buff[py - 1][px - 1]= L'�I';
			}
			else if(a <= 112.5) {
				if(inMap(veci(py, px - 1))) map_buff[py][px - 1]= L'��';
			}
			else if(a <= 157.5) {
				if(inMap(veci(py + 1, px - 1))) map_buff[py + 1][px - 1]= L'�L';
			}
			else {
				if(inMap(veci(py + 1, px))) map_buff[py + 1][px]= L'��';
			}
		}
	}
	map_buff[state.p[state.my].pos.y][state.p[state.my].pos.x]= L'��';
	for(int i= 0; i < MAP_SIZE_Y; i++)
		for(int j= 0; j < MAP_SIZE_X; j++)
			if(map_wall[i][j].health > 0) map_buff[i][j]= wall_char[map_wall[i][j].type];
}
void Game::OptThread() {
	INPUT_RECORD rec;
	HANDLE hin= GetStdHandle(STD_INPUT_HANDLE);
	DWORD fdwMode, fdwSaveOldMode;
	UNEXCEPT_DO(GetConsoleMode(hin, &fdwSaveOldMode));
	fdwMode= /*ENABLE_WINDOW_INPUT |*/ ENABLE_MOUSE_INPUT;
	UNEXCEPT_DO(SetConsoleMode(hin, fdwMode));
	DWORD dwread;
	while(1) {
		Sleep(10);
		UNEXCEPT_DO(PeekConsoleInput(hin, &rec, 1, &dwread));
		if(!ingame) break;
		if(dwread == 0) continue;
		UNEXCEPT_DO(ReadConsoleInput(hin, &rec, 1, &dwread));
		if(rec.EventType == MOUSE_EVENT) {
			if(rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
				lbtn= 1;
			}
			else if(lbtn) {
				lbtn= 0;
			}
			if(rec.Event.MouseEvent.dwEventFlags & MOUSE_MOVED) {
				mouse_pos.x= rec.Event.MouseEvent.dwMousePosition.X / 2;
				mouse_pos.y= rec.Event.MouseEvent.dwMousePosition.Y;
			}
		}
		else if(rec.EventType == KEY_EVENT) {
			if(rec.Event.KeyEvent.bKeyDown) {
				if(!btnstate[rec.Event.KeyEvent.wVirtualKeyCode]) {
					btnstate[rec.Event.KeyEvent.wVirtualKeyCode]= 1;
				}
			}
			else {
				if(btnstate[rec.Event.KeyEvent.wVirtualKeyCode]) {
					btnstate[rec.Event.KeyEvent.wVirtualKeyCode]= 0;
				}
			}
		}
	}
}
#endif

void Game::UpdateTurn(const Turn &turn) {
	for(int i= 0; i < state.cnt; i++) {
		switch(turn.opt[i].type) {
			case OT_KEYDOWN: {
				state.p[i].button[turn.opt[i].key.vk]= 1;
				break;
			}
			case OT_KEYUP: {
				state.p[i].button[turn.opt[i].key.vk]= 0;
				break;
			}
			case OT_MOUSEMOVE: {
				state.p[i].mouse_pos= turn.opt[i].mouse.pos;
				break;
			}
			case OT_MOUSELBTNDOWN: {
				state.p[i].lbtn= 1;
				break;
			}
			case OT_MOUSELBTNUP: {
				state.p[i].lbtn= 0;
				break;
			}
		}
	}
}
void Game::UpdatePlayerState(const Turn &turn) {
	for(int i= 0; i < state.cnt; i++) {
		if(state.p[i].remove) continue;
		if(turn.id - state.p[i].preupdate_move > 3) {
			state.p[i].preupdate_move= turn.id;
			if(state.p[i].button['W']) {
				if(!isWall(state.p[i].pos.x, state.p[i].pos.y - 1)) state.p[i].pos.y--;
			}
			if(state.p[i].button['A']) {
				if(!isWall(state.p[i].pos.x - 1, state.p[i].pos.y)) state.p[i].pos.x--;
			}
			if(state.p[i].button['S']) {
				if(!isWall(state.p[i].pos.x, state.p[i].pos.y + 1)) state.p[i].pos.y++;
			}
			if(state.p[i].button['D']) {
				if(!isWall(state.p[i].pos.x + 1, state.p[i].pos.y)) state.p[i].pos.x++;
			}
			state.p[i].pos.y= max(state.p[i].pos.y, 0);
			state.p[i].pos.y= min(state.p[i].pos.y, MAP_SIZE_Y - 1);
			state.p[i].pos.x= max(state.p[i].pos.x, 0);
			state.p[i].pos.x= min(state.p[i].pos.x, MAP_SIZE_X - 1);
			switch(map_item[state.p[i].pos.y][state.p[i].pos.x]) {
				case IT_RANDWEAPEN:
					if(state.p[i].flag_process == PT_RELOAD) {
						state.p[i].flag_process= 0;
						state.p[i].procbar= 0;
					}
					state.p[i].weapon= rand() % v_weapon.size();
					state.p[i].rest_bullet= GetPlayerWeapon(i).magazine;
					break;
			}
			map_item[state.p[i].pos.y][state.p[i].pos.x]= IT_NULL;
		}
		if(state.p[i].flag_process == PT_NULL) {
			if(turn.id - state.p[i].preupdate_shoot >= GetPlayerWeapon(i).shoot_delay) {
				if(state.p[i].lbtn && state.p[i].mouse_pos != veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2)) {
					state.p[i].preupdate_shoot= turn.id;
					Bullet b;
					b.base= GetPlayerWeapon(i).bullet;
					b.playerid= i;
					b.p= state.p[i].pos;
					b.pre_update= turn.id;
					for(int k= 0; k < min(state.p[i].rest_bullet, GetPlayerWeapon(i).bullet_pre_shoot); k++) {
						vecd endp= state.p[i].pos + (state.p[i].mouse_pos - veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2));
						b.v= BulletGetV(b.p, endp, GetPlayerWeapon(i).deviation);
						state.l_bt.push_back(b);
					}
					state.p[i].rest_bullet= max(state.p[i].rest_bullet - GetPlayerWeapon(i).bullet_pre_shoot, 0);
				}
			}
			if(state.p[i].button['R']) {
				state.p[i].flag_process= PT_RELOAD;
				state.p[i].procbar= GetPlayerWeapon(i).reload_time;
			}
		}
		else {
			if(--state.p[i].procbar <= 0) {
				switch(state.p[i].flag_process) {
					case PT_RELOAD: state.p[i].rest_bullet= GetPlayerWeapon(i).magazine; break;
				}
				state.p[i].flag_process= PT_NULL;
			}
		}
	}
}
void Game::UpdateBullte(const Turn &turn) {
	for(auto it= state.l_bt.begin(); it != state.l_bt.end();) {
		if(turn.id - it->pre_update < it->base.move_delay) {
			++it;
			continue;
		}
		for(int k= 0; k < it->base.move_pre_turn && inMap(it->p); k++) {
			it->pre_update= turn.id;
			it->p= it->p + it->v;
			if(map_wall[roundx(it->p.y)][roundx(it->p.x)].health > 0) {
				map_wall[roundx(it->p.y)][roundx(it->p.x)].health-= it->base.damage;
				it->p= veci(1000000, 1000000);
			}
			else {
				for(int i= 0; i < state.cnt; i++) {
					if(state.p[i].remove) continue;
					if(state.p[i].pos == it->p && it->playerid != i) {
						it->p= veci(1000000, 1000000);
						state.p[i].health-= it->base.damage;
						if(it->playerid == state.my) {
							damage+= it->base.damage;
						}
						if(state.p[i].health <= 0) {
							if(i == state.my) {
								killed_by= state.p[it->playerid].name;
							}
							if(it->playerid == state.my) {
								kills.push_back(state.p[i].name);
							}
							state.p[i].remove= 1;
							ReqOpt o;
							o.opt.type= OT_DEATH;
							o.opt.death.id= i;
							PackMessage(o);
							s.sendmsg(&o, &server);
							// MessageBoxA(0, state.p[i].name, "DEATH", 0);
						}
					}
				}
			}
		}
		if(inMap(it->p)) {
			++it;
		}
		else {
			it= state.l_bt.erase(it);
		}
	}
}

bool Game::CheckMyState() {
	if(state.p[state.my].lbtn != lbtn) return 0;
	if(state.p[state.my].mouse_pos != mouse_pos) return 0;
	for(int i= 0; i < 256; i++)
		if(state.p[state.my].button[i] != btnstate[i]) return 0;
	return 1;
}
void Game::UpdateMyState() {
	if(state.p[state.my].lbtn != lbtn) {
		ReqOpt o;
		o.opt.type= lbtn ? OT_MOUSELBTNDOWN : OT_MOUSELBTNUP;
		o.opt.mouse.pos= mouse_pos;
		PackMessage(o);
		UNEXCEPT_DO(s.sendmsg(&o, &server));
	}

	if(state.p[state.my].mouse_pos != mouse_pos) {
		ReqOpt o;
		o.opt.type= OT_MOUSEMOVE;
		o.opt.mouse.pos= mouse_pos;
		PackMessage(o);
		UNEXCEPT_DO(s.sendmsg(&o, &server));
	}

	for(int i= 0; i < 256; i++) {
		if(state.p[state.my].button[i] != btnstate[i]) {
			ReqOpt o;
			o.opt.type= btnstate[i] ? OT_KEYDOWN : OT_KEYUP;
			o.opt.key.vk= i;
			PackMessage(o);
			UNEXCEPT_DO(s.sendmsg(&o, &server));
		}
	}
}
int Game::GetAlivePlayerCnt() {
	int ret= 0;
	for(int i= 0; i < state.cnt; i++) {
		ret+= !state.p[i].remove;
	}
	return ret;
}
void Game::CreateWalls() {
	Wall w;
	w.type= 0;
	w.health= 50;
	for(int i= 0; i < 100; i++) {
		int x= rand() % (MAP_SIZE_X - 1), y= rand() % (MAP_SIZE_Y - 1);
		map_wall[y][x]= w;
		map_wall[y + 1][x]= w;
		map_wall[y][x + 1]= w;
		map_wall[y + 1][x + 1]= w;
	}
}
void Game::CreateItems(int num) {
	for(int i= 0; i < num; i++) {
		int x, y;
		do {
			y= rand() % MAP_SIZE_Y;
			x= rand() % MAP_SIZE_X;
		} while(!isWall(x, y));
		map_item[rand() % MAP_SIZE_Y][rand() % MAP_SIZE_X]= IT_RANDWEAPEN;
	}
}
void Game::CreatePlayers(const InitState &initstate) {
	for(int i= 0; i < 100; i++) {
		for(int i= 0; i < state.cnt; i++) {
			state.p[i].pos.x= rand() % MAP_SIZE_X;
			state.p[i].pos.y= rand() % MAP_SIZE_Y;
			state.p[i].health= 100;
			state.p[i].remove= 0;
			strcpy(state.p[i].name, initstate.name[i]);
		}
	}
}
void Game::GameThread() {
	// s.setblock(0);
	int64 pretime= 0;
	Turn turn;
	SOCKADDR_IN x;
	InitState initstate;
	s.recv(&initstate, sizeof(InitState), &server);
	srand(initstate.seed);
	state.cnt= initstate.playercnt;
	state.my= initstate.id;

	CreateWalls();

	CreatePlayers(initstate);

	CreateItems(50);

	fd_set fd;
	timeval ti= {5, 0};
	pretime= GetTime();
	while(1) {
		FD_ZERO(&fd);
		FD_SET(s.getsocket(), &fd);
		int ret= select(0, &fd, 0, 0, &ti);
		UNEXCEPT_DO(ret != SOCKET_ERROR);
		if(GetTime() - pretime > 5000) break;
		if(ret == 0) continue;
		UNEXCEPT_DO(s.recvmsg(&turn, &server));
		pretime= GetTime();
		// LOG("%d\n", GetTime() - pretime);

		UpdateTurn(turn);

		UpdateBullte(turn);

		UpdatePlayerState(turn);

		if(state.p[state.my].remove) {
			rank= GetAlivePlayerCnt() + 1;
			break;  // exit;
		}

#ifndef GAME_AI
		DrawConsoleBuffer();

		UpdateConsole();
#endif

		if(GetAlivePlayerCnt() == 1) {
			rank= 1;
			break;
		}

#ifdef GAME_AI
		if(!CheckMyState())
			UpdateMyState();
		else
			CiyangAI();
#else
		UpdateMyState();
#endif
	}
	ReqOpt o;
	o.opt.type= OT_DEATH;
	o.opt.death.id= state.my;
	PackMessage(o);
	UNEXCEPT_DO(s.sendmsg(&o, &server));
	ingame= 0;
}
void Game::AddWeapons(neb::CJsonObject &res) {
	Weapon w;
	int siz= res.GetArraySize();
	for(int i= 0; i < siz; i++) {
		res[i].Get("name", w.name);
		res[i].Get("shoot_delay", w.shoot_delay);
		res[i].Get("bullet_pre_shoot", w.bullet_pre_shoot);
		res[i].Get("magazine", w.magazine);
		res[i].Get("reload_time", w.reload_time);
		res[i].Get("deviation", w.deviation);
		res[i]["bullet"].Get("damage", w.bullet.damage);
		res[i]["bullet"].Get("move_delay", w.bullet.move_delay);
		res[i]["bullet"].Get("move_pre_turn", w.bullet.move_pre_turn);
		v_weapon.push_back(w);
	}
}
Game::Game() : ingame(0), btnstate(), lbtn(0), rbtn(0), killed_by() {
#ifndef GAME_AI
	SetConsoleSize(SIGHT_SIZE_X + STATEBAR_SIZE_X, SIGHT_SIZE_Y);
	hconbuf[0]= CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
	hconbuf[1]= CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
#endif
	memset(state.p, 0, sizeof(state.p));
	server.sin_family= AF_INET;
	server.sin_port= htons(12345);
	server.sin_addr.S_un.S_addr= inet_addr(SERVER_IP);
	// inet_pton(AF_INET, "172.22.21.53", &server.sin_addr);
	UNEXCEPT_DO(s.create());
}
Game::~Game() {
	s.close();
	CloseHandle(hconbuf[0]);
	CloseHandle(hconbuf[1]);
	SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
}
void Game::StartGame(const char *name) {
	ReqJoin x;
#ifdef GAME_AI
	x.isAI= 1;
#else
	x.isAI= 0;
#endif
	strcpy(x.name, name);
	PackMessage(x);
	s.sendmsg(&x, &server);
	MsgPort pt;
	s.recvmsg(&pt, &server);
	server.sin_port= htons(pt.port);
	s.send(0, 0, &server);

	ingame= 1;

	std::thread t_game(&Game::GameThread, this);
	thread_game.swap(t_game);
#ifndef GAME_AI
	std::thread t_opt(&Game::OptThread, this);
	thread_opt.swap(t_opt);
#endif
}
void Game::wait(GameReturnValue &ret) {
	thread_game.join();
#ifndef GAME_AI
	thread_opt.join();
#endif
	ret.damage= damage;
	ret.killed_by= killed_by;
	ret.kills= kills;
	ret.rank= rank;
}
void Game::ApplyResource(neb::CJsonObject &res) {
	AddWeapons(res["weapon"]);
}
