#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define GAME_AI
#include "../network/Socket.h"
#include "../network/Socket.cpp"
#include "../network/SocketUDP.h"
#include "../network/shared_def.h"
#include "..//network/CJsonObject.h"
#include "..//network/CJsonObject.cpp"
#include "..//network/cjSON.c"
#include <iostream>
#include <thread>
#include <list>
#include <queue>
#include <conio.h>
#include <io.h>
#include <windows.h>
#include <mutex>
#include "../network/Random.h"
#include <map>
using namespace std;
#define _TOSTR(x) #x
#define TOSTR(x) _TOSTR(x)
#define INTERRUPT_EXCEPTION(s) MessageBoxA(0, "exception: " s " .\n  at:\n    file:" __FILE__ "\n    line:" TOSTR(__LINE__) "\n", "", MB_ICONERROR | MB_OK)
#define LOG_EXCEPTION(s) LOG("exception: " s " .\n  at:\n    file:" __FILE__ "\n    line:" TOSTR(__LINE__) "\n")
#define TRY_DO(exp) (void)(!!(exp) || LOG_EXCEPTION(#exp " assert failed"))
#define UNEXCEPT_DO(exp) (void)(!!(exp) || (INTERRUPT_EXCEPTION(#exp " assert failed"), exit(0), 1))
#define IsKeyDown(vk) ((bool)(GetAsyncKeyState(vk) & 0x8000))
#define SEHTRY __try
#define SEHEXCEPT                                        \
	__except(1) {                                        \
		char buf[32];                                    \
		sprintf(buf, "ERROR: 0X%X", GetExceptionCode()); \
		MessageBoxA(0, buf, "", MB_ICONERROR);           \
	}

#define MAP_SIZE_X 100
#define MAP_SIZE_Y 100

#define SIGHT_SIZE_X 31
#define SIGHT_SIZE_Y 21

int LOG(const char *s, ...) {
	return 0;
	static FILE *f= fopen(("F:\\log"s + to_string(_getpid()) + ".txt"s).c_str(), "w");
	int _Result;
	va_list arg;
	__crt_va_start(arg, s);
	_Result= _vfprintf_l(f, s, NULL, arg);
	__crt_va_end(arg);
	fflush(f);
	return _Result;
}

vecd NextPoint(vecd s, vecd e) {
	vecd ret;
	double cnt= max(abs(s.x - e.x), abs(s.y - e.y));
	ret.x= s.x + (s.x - e.x) / cnt;
	ret.y= s.y + (s.y - e.y) / cnt;
	return ret;
}
struct BulletBase {
	int move_delay;
	int move_pre_turn;
	int damage;
};
struct Weapon {
	string name;
	int shoot_delay;
	int bullet_pre_shoot;
	int magazine;
	int reload_time;
	BulletBase bullet;
};
enum PROCESSTYPE {
	PT_NULL,
	PT_RELOAD,
};
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
struct Bullet {
	BulletBase base;
	int playerid;
	int pre_update;
	vecd p, e;
};
struct GameState {
	PlayerState p[50];
	list< Bullet > l_bt;
	uint16 my, cnt;
};

const wchar_t wall_char[]= L"□";
struct Wall {
	int type;
	int health;
};
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
	COORD siz;
	siz.X= rect.Right - rect.Left + 1;
	siz.Y= rect.Bottom - rect.Top + 1;
	int e= SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &rect);
	e= SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), siz);
	e= SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &rect);
}
struct GameReturnValue {
	string killed_by;
	vector< string > kills;
	int damage;
	int rank;
};
enum Item {
	IT_NULL,
	IT_RANDWEAPEN,
	IT_ADDHEALTH,
};
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
	COORD siz;
	siz.X= rect.Right - rect.Left + 1;
	siz.Y= rect.Bottom - rect.Top + 1;
	int e= SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &rect);
	e= SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), siz);
	e= SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &rect);
}
class Game {
	private:
	SocketUDP s;
	SOCKADDR_IN server;
	HANDLE hconnow;
	GameState state;
	bool ingame;
	bool btnstate[256];
	veci mouse_pos;
	bool lbtn, rbtn;
	//#ifndef GAME_AI
	string killed_by;
	vector< string > kills;
	vector< Weapon > v_weapon;
	wchar_t map_buff[MAP_SIZE_Y][MAP_SIZE_X];
	Wall map_wall[MAP_SIZE_Y][MAP_SIZE_X];
	Item map_item[MAP_SIZE_Y][MAP_SIZE_X];
	HANDLE hconbuf[2];
	int rank;
	int damage;
	//#endif
	thread thread_game;
#ifndef GAME_AI
	thread thread_opt;
#endif
	private:
	static bool inMap(int x, int y) {
		return x >= 0 && y >= 0 && x < MAP_SIZE_X && y < MAP_SIZE_Y;
	}
	static bool inMap(const veci &p) {
		return inMap(p.x, p.y);
	}
	bool isWall(int x, int y) {
		return map_wall[y][x].health > 0;
	}
	bool isWall(const veci &p) {
		return isWall(p.x, p.y);
	}
	const Weapon &GetPlayerWeapon(int x) {
		return v_weapon[state.p[x].weapon];
	}
#ifdef GAME_AI

	void CiyangAI() {
		static Random random(time(0));
		int mx= state.p[state.my].pos.x, my= state.p[state.my].pos.y, clPlayer;
		double mindis= 1e9;
		std::vector< int > scPlayer;
		for(int i= 0; i < state.cnt; i++) {
			if(i == state.my || state.p[i].remove) continue;
			if(abs(state.p[i].pos.x - mx) * 2 <= SIGHT_SIZE_X && abs(state.p[i].pos.y - my) * 2 <= SIGHT_SIZE_Y) scPlayer.push_back(i);
			if(mindis > (state.p[i].pos - state.p[state.my].pos).len()) mindis= (state.p[i].pos - state.p[state.my].pos).len(), clPlayer= i;
		}
		static std::map< int, std::map< int, bool > > arBullet, wp;
		static int moves[][2]= {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
		static char movesc[][3]= {"AW", "AA", "AS", "WW", "SS", "DW", "DD", "DS"};
		arBullet.clear();
		for(const auto &i : state.l_bt) {
			vecd nowb= i.p;
			for(int j= 1; j <= i.base.move_pre_turn; j++) {
				nowb= NextPoint(nowb, i.e);
				if(!inMap((int)nowb.x, (int)nowb.y)) break;
				if(abs((int)nowb.x - mx) <= 1 && abs((int)nowb.y - my) <= 1) arBullet[(int)nowb.x][(int)nowb.y]= 1;
				if(isWall((int)nowb.x, (int)nowb.y)) break;
			}
		}
		if(mindis > veci(SIGHT_SIZE_X, SIGHT_SIZE_Y).len()) lbtn= 0;
		btnstate['R']= 0;
		if(scPlayer.size() == 0) {
			if(rest_bullet != GetPlayerWeapon(x).magazine) btnstate['R']= 1;
			int nx, ny;
			btnstate['W']= btnstate['A']= btnstate['S']= btnstate['D']= lbtn= 0;
			struct CYNODE {
				int x, y, lastt;
			} nowno;
			std::queue< CYNODE > qu;
			for(int i= std::max(0, mx - SIGHT_SIZE_X / 2 + 1); i < std::min(mx + SIGHT_SIZE_X / 2, MAP_SIZE_X); i++)
				for(int j= std::max(0, my - SIGHT_SIZE_Y / 2 + 1); j < std::min(my + SIGHT_SIZE_Y / 2, MAP_SIZE_Y); j++) {
					wp[i][j]= 0;
					if(map_item[i][j]) qu.push((CYNODE){i, j, -1}), wp[i][j]= 1;
				}
			while(!qu.empty()) {
				nowno= qu.front(), qu.pop();
				if(nowno.x == mx || nowno.y == my) {
					int b= 7 - nowno.lastt;
					if(b <= 7) {
						for(int j= 0; j < 2; j++) btnstate[movesc[b][j]]= 1;
						return;
					}
					break;
				}
				for(int i= 0; i < 8; i++) {
					nx= nowno.x + moves[i][0], ny= nowno.y + moves[i][1];
					if(!inMap(nx, ny) || isWall(nx, my) || isWall(mx, ny) || isWall(nx, ny) || arBullet[nx][ny] || wp[nx][ny]) continue;
					qu.push((CYNODE){nx, ny, i}), wp[nx][ny]= 1;
				}
			}
			if(arBullet[nx][ny] == 0) return;
			std::vector< int > canu;
			for(int i= 0; i < 8; i++) {
				nx= mx + moves[i][0], ny= my + moves[i][1];
				if(!inMap(nx, ny) || isWall(nx, my) || isWall(mx, ny) || isWall(nx, ny) || arBullet[nx][ny]) continue;
				canu.push_back(i);
			}
			if(!canu.empty()) {
				int num= rand() % canu.size();
				for(int j= 0; j < 2; j++) btnstate[movesc[canu[num]][j]]= 1;
				return;
			}
			for(int i= 0; i < 8; i++) {
				if(moves[i][0] != 0 && moves[i][1] != 0) continue;
				nx= mx + moves[i][0], ny= my + moves[i][1];
				if(!inMap(nx, ny) || arBullet[nx][ny]) continue;
				canu.push_back(i);
				return;
			}
			if(!canu.empty()) {
				int num= rand() % canu.size();
				nx= mx + moves[canu[num]][0], ny= my + moves[canu[num]][1];
				mouse_pos= veci(nx, ny) - state.p[state.my].pos + veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2), lbtn= 1;
				for(int j= 0; j < 2; j++) btnstate[movesc[canu[num]][j]]= 1;
				return;
			}
			int num= rand() % 8;
			for(int j= 0; j < 2; j++) btnstate[movesc[num][j]]= 1;
		}
		else if(scPlayer.size() == 1) {
			int nx, ny;
			std::vector< int > canu;
			btnstate['W']= btnstate['A']= btnstate['S']= btnstate['D']= 0;
			for(int i= 0; i < 8; i++) {
				nx= mx + moves[i][0], ny= my + moves[i][1];
				if(!inMap(nx, ny) || isWall(nx, my) || isWall(mx, ny) || isWall(nx, ny) || arBullet[nx][ny]) continue;
				canu.push_back(i);
			}
			if(!canu.empty()) {
				int num= rand() % canu.size();
				for(int j= 0; j < 2; j++) btnstate[movesc[canu[num]][j]]= 1;
			}
			else {
				int num= rand() % 8;
				for(int j= 0; j < 2; j++) btnstate[movesc[num][j]]= 1;
			}
			mouse_pos= state.p[scPlayer[0]].pos - state.p[state.my].pos + veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2), lbtn= 1;
		}
		else {
			if(btnstate['W'] && (!inMap(mx, my - 1) || isWall(mx, my - 1))) {
				btnstate['W']= 0;
				if(rand() % 2) btnstate['D']= 1;
				if(rand() % 2) btnstate['A']= 1;
			}
			if(btnstate['A'] && (!inMap(mx - 1, my) || isWall(mx - 1, my))) {
				btnstate['A']= 0, btnstate['D']= 1;
				if(rand() % 2) btnstate['S']= 1;
			}
			if(btnstate['S'] && (!inMap(mx, my + 1) || isWall(mx, my + 1))) {
				btnstate['S']= 0, btnstate['D']= 1;
			}
			else if(btnstate['D'] && (!inMap(mx + 1, my) || isWall(mx + 1, my))) {
				btnstate['D']= 0;
				if(rand() % 2) btnstate['W']= 1;
				if(rand() % 2) btnstate['S']= 1;
			}
			mouse_pos= state.p[clPlayer].pos - state.p[state.my].pos + veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2), lbtn= 1;
		}
		return;
	}

	void AI() {
		static Random random(time(0));
		int mx= state.p[state.my].pos.x;
		int my= state.p[state.my].pos.y;
		if(btnstate['W'] && (!inMap(mx, my - 1) || isWall(mx, my - 1))) {
			btnstate['W']= 0;
			btnstate[random.rand() % 2 ? 'D' : 'A']= 1;
		}
		else if(btnstate['A'] && (!inMap(mx - 1, my) || isWall(mx - 1, my))) {
			btnstate['A']= 0;
			btnstate[random.rand() % 2 ? 'W' : 'S']= 1;
		}
		else if(btnstate['S'] && (!inMap(mx, my + 1) || isWall(mx, my + 1))) {
			btnstate['S']= 0;
			btnstate[random.rand() % 2 ? 'D' : 'A']= 1;
		}
		else if(btnstate['D'] && (!inMap(mx + 1, my) || isWall(mx + 1, my))) {
			btnstate['D']= 0;
			btnstate[random.rand() % 2 ? 'W' : 'S']= 1;
		}
		else {
			int ran= random.rand() % 1000;
			if(ran < 300) {
				char vk;
				switch(random.rand() % 4) {
					case 0: vk= 'W'; break;
					case 1: vk= 'A'; break;
					case 2: vk= 'S'; break;
					case 3: vk= 'D'; break;
				}
				btnstate[vk]= !btnstate[vk];
			}
			else if(ran < 800) {
				veci mindispos;
				int mindis= 1e9;
				for(int i= 0; i < state.cnt; i++) {
					if(i == state.my) continue;
					if(mindis > (state.p[i].pos - state.p[state.my].pos).len()) {
						mindis= (state.p[i].pos - state.p[state.my].pos).len();
						mindispos= state.p[i].pos - state.p[state.my].pos + veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2);
					}
				}
				mouse_pos= mindispos;
			}
			else {
				if(random.rand() % 10 == 0)
					lbtn= 0;
				else
					lbtn= 1;
			}
		}
	}
#endif
#ifndef GAME_AI
	void UpdateConsole() {
		static wchar_t buffer[SIGHT_SIZE_Y + 1][SIGHT_SIZE_X + STATEBAR_SIZE_X];

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
					buffer[i][j]= L'∷';  // ∷×
			}
		}

		for(int i= 0; i < SIGHT_SIZE_Y; i++) {
			buffer[i][SIGHT_SIZE_X]= L'|';
		}

		swprintf(&buffer[0][SIGHT_SIZE_X + 2], L"weapon:%hs", GetPlayerWeapon(state.my).name.c_str());
		swprintf(&buffer[1][SIGHT_SIZE_X + 2], L"magazine:%d/%d", state.p[state.my].rest_bullet, GetPlayerWeapon(state.my).magazine);
		swprintf(&buffer[2][SIGHT_SIZE_X + 2], L"timer:%d", state.p[state.my].procbar);

		int health_bar= SIGHT_SIZE_X * state.p[state.my].health / 100;
		for(int i= 0; i < SIGHT_SIZE_X; i++) buffer[SIGHT_SIZE_Y][i]= i < health_bar ? L'■' : L'□';
		for(int i= 0; i < SIGHT_SIZE_Y + 1; i++) {
			DWORD dw;
			WriteConsoleOutputCharacter(hconbuf[p], (LPCWSTR)buffer[i], SIGHT_SIZE_X + STATEBAR_SIZE_X, COORD{(SHORT)0, (SHORT)i}, &dw);
		}
		SetConsoleActiveScreenBuffer(hconbuf[p]);
		hconnow= hconbuf[p];
	}
	void DrawConsoleBuffer() {
		for(int i= 0; i < MAP_SIZE_Y; i++)
			for(int j= 0; j < MAP_SIZE_X; j++) map_buff[i][j]= L'　';

		for(int i= 0; i < MAP_SIZE_Y; i++)
			for(int j= 0; j < MAP_SIZE_X; j++)
				if(map_item[i][j] != 0) {
					switch(map_item[i][j]) {
						case IT_RANDWEAPEN:
							map_buff[i][j]= L'卍';
							// case IT_HEAL:map_buff[i][j] = L'卍';
					}
				}

		for(const auto &b : state.l_bt) {
			if(inMap(b.p)) map_buff[(int)b.p.y][(int)b.p.x]= L'·';
		}

		for(int i= 0; i < state.cnt; i++) {
			if(state.p[i].remove) continue;
			int px= state.p[i].pos.x, py= state.p[i].pos.y;
			map_buff[py][px]= L'○';
			wchar_t wc= L'　';
			vecd vertical(0, -1);
			vecd v= state.p[i].mouse_pos - vecd(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2);
			//↑↗→↘↓←↙↖
			double cosx= vertical * v / vertical.len() / v.len();
			double a= acos(vertical * v / vertical.len() / v.len()) * 180 / PI;
			if((vertical ^ v) > 0) {
				if(a <= 22.5) {
					if(inMap(veci(py - 1, px))) map_buff[py - 1][px]= L'↑';
				}
				else if(a <= 67.5) {
					if(inMap(veci(py - 1, px + 1))) map_buff[py - 1][px + 1]= L'↗';
				}
				else if(a <= 112.5) {
					if(inMap(veci(py, px + 1))) map_buff[py][px + 1]= L'→';
				}
				else if(a <= 157.5) {
					if(inMap(veci(py + 1, px + 1))) map_buff[py + 1][px + 1]= L'↘';
				}
				else {
					if(inMap(veci(py + 1, px))) map_buff[py + 1][px]= L'↓';
				}
			}
			else {
				if(a <= 22.5) {
					if(inMap(veci(py - 1, px))) map_buff[py - 1][px]= L'↑';
				}
				else if(a <= 67.5) {
					if(inMap(veci(py - 1, px - 1))) map_buff[py - 1][px - 1]= L'↖';
				}
				else if(a <= 112.5) {
					if(inMap(veci(py, px - 1))) map_buff[py][px - 1]= L'←';
				}
				else if(a <= 157.5) {
					if(inMap(veci(py + 1, px - 1))) map_buff[py + 1][px - 1]= L'↙';
				}
				else {
					if(inMap(veci(py + 1, px))) map_buff[py + 1][px]= L'↓';
				}
			}
		}
		map_buff[state.p[state.my].pos.y][state.p[state.my].pos.x]= L'●';
		for(int i= 0; i < MAP_SIZE_Y; i++)
			for(int j= 0; j < MAP_SIZE_X; j++)
				if(map_wall[i][j].health > 0) map_buff[i][j]= wall_char[map_wall[i][j].type];
	}
	void OptThread() {
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
					LOG("mouse down\n");
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
						LOG("down: %c\n", rec.Event.KeyEvent.wVirtualKeyCode);
					}
				}
				else {
					if(btnstate[rec.Event.KeyEvent.wVirtualKeyCode]) {
						btnstate[rec.Event.KeyEvent.wVirtualKeyCode]= 0;
						LOG("up: %c\n", rec.Event.KeyEvent.wVirtualKeyCode);
					}
				}
			}
		}
	}
#endif

	void UpdateTurn(const Turn &turn) {
		for(int i= 0; i < state.cnt; i++) {
			switch(turn.opt[i].type) {
				case OT_KEYDOWN: {
					LOG("recv down:%c\n", turn.opt[i].key.vk);
					state.p[i].button[turn.opt[i].key.vk]= 1;
					break;
				}
				case OT_KEYUP: {
					LOG("recv up:%c\n", turn.opt[i].key.vk);
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
	void UpdatePlayerState(const Turn &turn) {
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
						state.p[i].weapon= rand() % v_weapon.size();
						state.p[i].rest_bullet= GetPlayerWeapon(i).magazine;
						break;
				}
				map_item[state.p[i].pos.y][state.p[i].pos.x]= IT_NULL;
			}
			if(state.p[i].flag_process == PT_NULL) {
				if(turn.id - state.p[i].preupdate_shoot >= GetPlayerWeapon(i).shoot_delay) {
					if(state.p[i].lbtn) {
						state.p[i].preupdate_shoot= turn.id;
						Bullet b;
						b.base= GetPlayerWeapon(i).bullet;
						b.playerid= i;
						b.p= state.p[i].pos;
						b.pre_update= turn.id;
						for(int k= 0; k < min(state.p[i].rest_bullet, GetPlayerWeapon(i).bullet_pre_shoot); k++) {
							b.e= state.p[i].pos + (state.p[i].mouse_pos - veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2)) * 100;
							b.e= vecd(0, 0) - b.e;
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
	void UpdateBullte(const Turn &turn) {
		for(auto it= state.l_bt.begin(); it != state.l_bt.end();) {
			if(turn.id - it->pre_update < it->base.move_delay) {
				++it;
				continue;
			}
			for(int k= 0; k < it->base.move_pre_turn && inMap(it->p); k++) {
				it->pre_update= turn.id;
				it->p= NextPoint(it->p, it->e);
				if(map_wall[(int)it->p.y][(int)it->p.x].health > 0) {
					map_wall[(int)it->p.y][(int)it->p.x].health-= it->base.damage;
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

	void CheckAndUpdateMyState() {
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
	int GetAlivePlayerCnt() {
		int ret= 0;
		for(int i= 0; i < state.cnt; i++) {
			ret+= !state.p[i].remove;
		}
		return ret;
	}
	void CreateWalls() {
		Wall w;
		w.type= 0;
		w.health= 50;
		for(int i= 0; i < 500; i++) {
			map_wall[rand() % MAP_SIZE_Y][rand() % MAP_SIZE_X]= w;
		}
	}
	void CreateItems(int num) {
		for(int i= 0; i < num; i++) {
			int x, y;
			do {
				y= rand() % MAP_SIZE_Y;
				x= rand() % MAP_SIZE_X;
			} while(!isWall(x, y));
			map_item[rand() % MAP_SIZE_Y][rand() % MAP_SIZE_X]= IT_RANDWEAPEN;
		}
	}
	void CreatePlayers(const InitState &initstate) {
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
	void GameThread() {
		// s.setblock(0);
		int64 pretime= 0;
		Turn turn;
		SOCKADDR_IN x;
		InitState initstate;
		LOG("s.recv InitState...\n");
		s.recv(&initstate, sizeof(InitState), &server);
		LOG("s.recv InitState done.\n");
		srand(initstate.seed);
		state.cnt= initstate.playercnt;
		state.my= initstate.id;

		CreateWalls();

		CreatePlayers(initstate);

		CreateItems(100);

		fd_set fd;
		timeval ti= {5, 0};
		while(1) {
			FD_ZERO(&fd);
			FD_SET(s.getsocket(), &fd);
			int ret= select(0, &fd, 0, 0, &ti);
			UNEXCEPT_DO(ret != SOCKET_ERROR);
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
			AI();
#endif

			CheckAndUpdateMyState();
		}
		ReqOpt o;
		o.opt.type= OT_DEATH;
		o.opt.death.id= state.my;
		PackMessage(o);
		UNEXCEPT_DO(s.sendmsg(&o, &server));
		ingame= 0;
	}
	void AddWeapons(CJsonObject &res) {
		Weapon w;
		int siz= res.GetArraySize();
		for(int i= 0; i < siz; i++) {
			res[i].Get("name", w.name);
			res[i].Get("shoot_delay", w.shoot_delay);
			res[i].Get("bullet_pre_shoot", w.bullet_pre_shoot);
			res[i].Get("magazine", w.magazine);
			res[i].Get("reload_time", w.reload_time);
			res[i]["bullet"].Get("damage", w.bullet.damage);
			res[i]["bullet"].Get("move_delay", w.bullet.move_delay);
			res[i]["bullet"].Get("move_pre_turn", w.bullet.move_pre_turn);
			v_weapon.push_back(w);
		}
	}

	public:
	Game() : ingame(0), btnstate(), lbtn(0), rbtn(0), killed_by() {
#ifndef GAME_AI
		SetConsoleSize(SIGHT_SIZE_X + STATEBAR_SIZE_X, SIGHT_SIZE_Y);
		hconbuf[0]= CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
		hconbuf[1]= CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
#endif
		memset(state.p, 0, sizeof(state.p));
		server.sin_family= AF_INET;
		server.sin_port= htons(12345);
		server.sin_addr.S_un.S_addr= inet_addr("172.22.21.55");
		// inet_pton(AF_INET, "172.22.21.55", &server.sin_addr);
		UNEXCEPT_DO(s.create());
	}
	~Game() {
		s.close();
		CloseHandle(hconbuf[0]);
		CloseHandle(hconbuf[1]);
		SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
	}
	void StartGame(const char *name) {
		ReqJoin x;
#ifdef GAME_AI
		x.isAI= 1;
#else
		x.isAI= 0;
#endif
		strcpy(x.name, name);
		PackMessage(x);
		LOG("s.sendmsg ReqJoin...\n");
		s.sendmsg(&x, &server);
		LOG("s.sendmsg ReqJoin done.\n");
		MsgPort pt;
		LOG("s.recvmsg MsgPort...\n");
		s.recvmsg(&pt, &server);
		LOG("s.recvmsg MsgPort done.\n");
		server.sin_port= htons(pt.port);
		s.send(0, 0, &server);

		ingame= 1;

		thread t_game(&Game::GameThread, this);
		thread_game.swap(t_game);
#ifndef GAME_AI
		thread t_opt(&Game::OptThread, this);
		thread_opt.swap(t_opt);
#endif
	}
	void wait(GameReturnValue &ret) {
		thread_game.join();
#ifndef GAME_AI
		thread_opt.join();
#endif
		ret.damage= damage;
		ret.killed_by= killed_by;
		ret.kills= kills;
		ret.rank= rank;
	}
	void ApplyResource(CJsonObject &res) {
		AddWeapons(res["weapon"]);
	}
};

void setcur(SHORT x, SHORT y) {
	HANDLE hout= GetStdHandle(STD_OUTPUT_HANDLE);
	UNEXCEPT_DO(hout != 0 && hout != INVALID_HANDLE_VALUE);
	COORD pos= {x, y};
	SetConsoleCursorPosition(hout, pos);
}
char name[32];

void StartGameX(Game *game) {
	SEHTRY {
		game->StartGame("AI");
		printf("wait other players...\n");
		game->wait();
	}
	SEHEXCEPT;
}

int main() {
	setlocale(LC_ALL, "");
	UNEXCEPT_DO(SocketUDP::init());
	setcur(0, 0);
	system("cls");
	Game *game= new Game();
	StartGameX(game);
	// game->StartGame("AI");
	// printf("wait other players...\n");
	// game->wait();
	return 0;
}
