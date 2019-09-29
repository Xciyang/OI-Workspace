#pragma once
#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Socket.h"
#include "SocketUDP.h"
#include "shared_def.h"
#include "CJsonObject.h"
#include <list>
#include <vector>
#include <string>
#include <thread>


#define _TOSTR(x) #x
#define TOSTR(x) _TOSTR(x)
#define INTERRUPT_EXCEPTION(s) MessageBoxA(0,"exception: " s " .\n  at:\n    file:" __FILE__ "\n    line:" TOSTR(__LINE__) "\n","",MB_ICONERROR|MB_OK)
#define LOG_EXCEPTION(s) LOG("exception: " s " .\n  at:\n    file:" __FILE__ "\n    line:" TOSTR(__LINE__) "\n")
#define TRY_DO(exp) (void)(!!(exp)||LOG_EXCEPTION(#exp " assert failed"))
#define UNEXCEPT_DO(exp) (void)(!!(exp)||(INTERRUPT_EXCEPTION(#exp " assert failed"),exit(0),1))
#define IsKeyDown(vk) ((bool)(GetAsyncKeyState(vk) & 0x8000))
#define SEHTRY __try
#define SEHEXCEPT __except (1) { char buf[32];sprintf(buf,"ERROR: 0X%X", GetExceptionCode());MessageBoxA(0,buf,"",MB_ICONERROR);}

#define MAP_SIZE_X 100
#define MAP_SIZE_Y 100

#define SIGHT_SIZE_X 31
#define SIGHT_SIZE_Y 21

#define STATEBAR_SIZE_X 20

#define SERVER_IP "172.22.21.53"
inline double randdouble() {
	return ((double)(((long long)rand() << 15 | rand()) + 1)) / (RAND_MAX << 15 | RAND_MAX);
}
inline vecd getv(vecd v) {
	return v / v.len();
}
inline double deviation(double maxd) {
	return randdouble() * maxd * 2 - maxd;
}
inline vecd BulletGetE(vecd s, vecd e, double dev) {
	vecd czv = getv((e - s).rotate(PI / 2));
	return e + czv * deviation(dev);
}
inline vecd LengthAmend(vecd v) {
	return getv(v) * 10;
}
inline vecd BulletGetV(vecd s, vecd e, double dev) {
	vecd czv = getv((e - s).rotate(PI / 2));
	return getv(e + czv * deviation(dev) - s);
}

//vecd NextPoint(vecd s, vecd e);
struct BulletBase {
	int move_delay;
	int move_pre_turn;
	int damage;
};
struct Weapon {
	std::string name;
	int shoot_delay;
	int bullet_pre_shoot;
	int magazine;
	int reload_time;
	double deviation;
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
	vecd p, v;
};
struct GameState {
	PlayerState p[50];
	std::list<Bullet>l_bt;
	uint16 my, cnt;
};

const wchar_t wall_char[] = L"¡õ";
struct Wall {
	int type;
	int health;
};
void SetConsoleSize(int X, int Y);
struct GameReturnValue {
	std::string killed_by;
	std::vector<std::string> kills;
	int damage;
	int rank;
};
enum Item {
	IT_NULL,
	IT_RANDWEAPEN,
	IT_ADDHEALTH,
};
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
	std::string killed_by;
	std::vector<std::string> kills;
	std::vector<Weapon> v_weapon;
	wchar_t map_buff[MAP_SIZE_Y][MAP_SIZE_X];
	Wall map_wall[MAP_SIZE_Y][MAP_SIZE_X];
	Item map_item[MAP_SIZE_Y][MAP_SIZE_X];
	HANDLE hconbuf[2];
	int rank;
	int damage;
	//#endif
	std::thread thread_game;
#ifndef GAME_AI	
	std::thread thread_opt;
#endif
private:
	static bool inMap(int x, int y);
	static bool inMap(const veci& p);
	bool isWall(int x, int y);
	bool isWall(const veci& p);
	const Weapon& GetPlayerWeapon(int x);
#ifdef GAME_AI
	void CiyangAI();
#endif
#ifndef GAME_AI
	void UpdateConsole();
	void DrawConsoleBuffer();
	void OptThread();
#endif
	void UpdateTurn(const Turn& turn);
	void UpdatePlayerState(const Turn& turn);
	void UpdateBullte(const Turn& turn);
	bool CheckMyState();
	void UpdateMyState();
	int GetAlivePlayerCnt();
	void CreateWalls();
	void CreateItems(int num);
	void CreatePlayers(const InitState& initstate);
	void GameThread();
	void AddWeapons(neb::CJsonObject& res);
public:
	Game();
	~Game();
	void StartGame(const char* name);
	void wait(GameReturnValue& ret);
	void ApplyResource(neb::CJsonObject& res);
};