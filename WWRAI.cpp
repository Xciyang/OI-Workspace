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
#ifdef GAME_AI
void Game::CiyangAI() {

	static const int AI_DEBUG = 0;

	static const int STATUS_WAIT = 1;
	static const int STATUS_ATTACK = 2;
	static const int STATUS_AWAY = 4;
	static const int STATUS_FIND = 8;
	static const int STATUS_WANDER = 16;

	static const double VIEW_SIZE_X = SIGHT_SIZE_X * 1.5;
	static const double VIEW_SIZE_Y = SIGHT_SIZE_Y * 1.5;
	static const int BULLET_ACROSS_WALL = 2;
	static const int BULLET_ACCURATE = 10;
	static const int RAND_LIMIT = 30;

	static const int SA_TIMES = 2;
	static const double SA_BEGIN = (MAP_SIZE_X + MAP_SIZE_Y) * 2;
	static const double SA_END = 1e-6;
	static const double SA_SPEED = 0.95;


	static Random random(time(0));

	struct AI_STATE {
		int status;
		int gox, goy, awayx, awayy;
		AI_STATE() {
			status = STATUS_WAIT;
			awayx = awayy = gox = goy = ~0x3f3f3f3f;
		}
	};
	struct vec3 { int x, y, z; };
	static AI_STATE aiState = AI_STATE();
	int opt = 0, closePlayer = -1, nowx = state.p[state.my].pos.x, nowy = state.p[state.my].pos.y;
	std::vector< int > sceenPlayers;
	double closeDis = 1e19;
	static int PlayerMap[MAP_SIZE_X][MAP_SIZE_Y], wp[MAP_SIZE_X][MAP_SIZE_Y][9], BulletMap[MAP_SIZE_X][MAP_SIZE_Y];

	if (AI_DEBUG)printf("\n Iam on %d %d\n", nowx, nowy);

	if (AI_DEBUG)printf("work");

	auto checkAllPlayer = [&, this]() -> void {
		if (closePlayer != -1) return;
		memset(PlayerMap, 0, sizeof(PlayerMap));
		for (int i = 0; i < state.cnt; i++) {
			if (i == state.my || state.p[i].remove) continue;
			if (abs(state.p[i].pos.x - nowx) <= VIEW_SIZE_X && abs(state.p[i].pos.y - nowy) <= VIEW_SIZE_Y) sceenPlayers.push_back(i);
			double tmpDis = (state.p[i].pos - state.p[state.my].pos).len();
			if (closeDis > tmpDis) closeDis = tmpDis, closePlayer = i;
			PlayerMap[state.p[i].pos.x][state.p[i].pos.y] = i + 1;
		}
		if (AI_DEBUG)printf("-checkplayer-");
		return;
	};
	static int nbtnstate[4], availableStep[9], moves[][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
	static char controlMove[] = "WASD", moveNeed[][5] = { "1100", "0100", "0110", "1000", "0010", "1001", "0001", "0011" };
	int hadgeta = 0, headgetb = 0;
	auto getAvailableStep = [&, this]() -> void {
		if (hadgeta) return;
		hadgeta = 1;
		for (int i = 0; i < 9; i++) availableStep[i] = -1;
		for (int j = 0; j < 4; j++) nbtnstate[j] = btnstate[controlMove[j]];
		if (nbtnstate[0] && nbtnstate[2]) nbtnstate[0] = nbtnstate[2] = 0;
		if (nbtnstate[1] && nbtnstate[3]) nbtnstate[1] = nbtnstate[3] = 0;
		if (!(nbtnstate[0] && nbtnstate[1] && nbtnstate[2] && nbtnstate[3])) availableStep[8] = 5;
		for (int j = 0, k; j < 8; j++) {
			for (k = 0; k < 4; k++)
				if (nbtnstate[k] != moveNeed[j][k] - '0') break;
			if (k == 4) availableStep[j] = 5;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) nbtnstate[j] = btnstate[controlMove[j]];
			nbtnstate[i] ^= 1;
			if (nbtnstate[0] && nbtnstate[2]) nbtnstate[0] = nbtnstate[2] = 0;
			if (nbtnstate[1] && nbtnstate[3]) nbtnstate[1] = nbtnstate[3] = 0;
			if (!(nbtnstate[0] && nbtnstate[1] && nbtnstate[2] && nbtnstate[3]) && availableStep[8] == -1) availableStep[8] = i;
			for (int j = 0, k; j < 8; j++) {
				if (availableStep[j] != -1) continue;
				for (k = 0; k < 4; k++)
					if (nbtnstate[k] != moveNeed[j][k] - '0') break;
				if (k == 4) availableStep[j] = i;
			}
		}
		if (AI_DEBUG) {
			printf("-checkstep-");
			for (int i = 0; i <= 8; i++) printf("/%d/", availableStep[i]);
		}
		return;
	};
	auto checkAllBullet = [&, this]() -> void {
		if (headgetb) return;
		headgetb = 1;
		memset(BulletMap, 0, sizeof(BulletMap));
		for (const auto& i : state.l_bt) {
			if (i.playerid == state.my) continue;
			vecd nowb = i.p;
			for (int j = 1; j <= i.base.move_pre_turn / i.base.move_delay; j++) {
				nowb = nowb + i.v;
				if (!inMap(roundx(nowb.x), roundx(nowb.y))) break;
				++BulletMap[roundx(nowb.x)][roundx(nowb.y)];
				if (isWall(roundx(nowb.x), roundx(nowb.y)) && BulletMap[roundx(nowb.x)][roundx(nowb.y)] <= 1) break;
			}
		}
		if (AI_DEBUG) printf("-checkbullet-");
	};
	auto BFSNextPos = [&, this](std::queue< vec3 >& qu, int awaybul) -> int {
		getAvailableStep();
		memset(wp, 0, sizeof(wp));
		vec3 nown, to;
		while (!qu.empty()) {
			nown = qu.front(), qu.pop();
			wp[nown.x][nown.y][nown.z] = 1;
			if (nown.x == nowx && nown.y == nowy) {
				int z = (nown.z == 8 ? 8 : 7 - nown.z);
				if (availableStep[z] != -1) return z;
				continue;
			}
			for (int i = 0; i < 8; i++) {
				to.x = nown.x + moves[i][0], to.y = nown.y + moves[i][1];
				if (!inMap(to.x, to.y) || isWall(to.x, to.y) || wp[to.x][to.y][i]) continue;
				if (awaybul && BulletMap[to.x][to.y]) continue;
				to.z = i;
				qu.push(to), wp[to.x][to.y][to.z] = 1;
			}
		}
		if (AI_DEBUG) printf("-BFS-");
		return 9;
	};
	auto checkMousePos = [&, this]() -> int {
		int atp = 0, cwall = 0;
		for (vecd bp = state.p[state.my].pos,
			bv = getv(state.p[state.my].pos, state.p[state.my].pos + (mouse_pos - veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2)));
			(bp - state.p[state.my].pos).len() < closeDis + 1 && inMap(roundx(bp.x), roundx(bp.y));
			bp = bp + bv) {
			if (PlayerMap[roundx(bp.x)][roundx(bp.y)]) return 1;
			if (isWall(roundx(bp.x), roundx(bp.y))) {
				if (++cwall >= BULLET_ACROSS_WALL) return 0;
			}
			else for (int j = 0; j < 8; j++) {
				int jx = roundx(bp.x) + moves[j][0], jy = roundx(bp.y) + moves[j][1];
				if (inMap(jx, jy) && PlayerMap[jx][jy]) ++atp;
			}
		}
		if (AI_DEBUG)printf("-checkmouse-");
		return atp < BULLET_ACCURATE ? 0 : 2;
	};
	auto checkOpt = [&, this](bool& ch, const bool& st) -> int {
		if (opt) return 0;
		if (ch != st) opt = 1, ch = st;
		return 1;
	};
	auto findFarestPoint = [&, this]() -> veci {
		int bestx = nowx, besty = nowy;
		auto calc = [&, this](int x, int y)-> double {
			double sumc = 1e19;
			for (int i = 0; i < state.cnt; i++) {
				if (i == state.my || state.p[i].remove) continue;
				sumc = min(sumc, (state.p[i].pos - veci(x, y)).len());
			}
			return sumc;
		};
		auto Rand = [this]() ->double {
			return (double)(random.rand() % 0x7f) / 0x7f;
		};
		double bestres = calc(bestx, besty);
		int times = 0;
		while (++times < SA_TIMES) {
			int sax = bestx, say = besty, sares = bestres;
			for (double T = SA_BEGIN; T > SA_END; T *= SA_SPEED) {
				int nxtx = sax + T * (Rand() - 0.5), nxty = say + T * (Rand() - 0.5);
				while (!inMap(nxtx, nxty)) nxtx = sax + T * (Rand() - 0.5), nxty = say + T * (Rand() - 0.5);
				double tmpres = calc(nxtx, nxty);
				if (tmpres >= bestres) bestres = tmpres, bestx = nxtx, besty = nxty;
				if (tmpres >= sares) sares = tmpres, sax = nxtx, say = nxty;
				else if (Rand() < exp((tmpres - sares) / T)) sax = nxtx, say = nxty;
			}
		}
		if (AI_DEBUG)printf("-sa-");
		return veci(bestx, besty);
	};	// By Simulated Annealing (Unadjusted)
	if (AI_DEBUG)printf("work2");
	while (!opt) {
		if (aiState.status & STATUS_WAIT) {
			if (AI_DEBUG) printf("wait");
			checkAllPlayer();
			if (sceenPlayers.size() == 0)
				aiState.status |= STATUS_WANDER, checkOpt(lbtn, 0);
			else
				aiState.status ^= (STATUS_ATTACK | STATUS_WAIT);
			if (AI_DEBUG) printf("wait2, my st:%d", aiState.status);
		}
		if (opt) break;
		if (aiState.status & STATUS_ATTACK) {
			if (AI_DEBUG) printf("attack");
			checkAllPlayer();
			if (sceenPlayers.size() == 0) {
				aiState.status ^= (STATUS_ATTACK | STATUS_WAIT);
				continue;
			}
			/*workwork2wait-checkplayer-wait2attackfind-checkbullet-***end****/
			if (state.p[state.my].flag_process == PT_RELOAD) {
				checkOpt(btnstate['R'], 0);
				aiState.status |= STATUS_FIND;
			}
			else if ((state.p[state.my].rest_bullet == 0 || (closeDis + 1 > GetPlayerWeapon(state.my).reload_time / 5 && state.p[state.my].rest_bullet < 5))) {
				checkOpt(btnstate['R'], 1);
				aiState.status |= STATUS_FIND;
			}
			else {
				if (!lbtn) 	checkOpt(lbtn, 1);
				else if (!checkMousePos()) {
					veci lmouse = mouse_pos;
					mouse_pos = state.p[closePlayer].pos - state.p[state.my].pos + veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2);
					if (!checkMousePos())
						mouse_pos = lmouse, checkOpt(lbtn, 0);
					else
						opt = 1;
				}
			}
			if (!lbtn || random.rand() % 2) {
				if (sceenPlayers.size() == 1)
					aiState.status |= STATUS_WANDER;
				else
					aiState.status |= STATUS_AWAY;
			}
		}
		if (opt) break;
		if (aiState.status & STATUS_FIND) {
			if (AI_DEBUG) printf("find");
			checkAllBullet();
			std::queue< vec3 > qu;
			for (int i = 0; i < MAP_SIZE_X; i++)
				for (int j = 0; j < MAP_SIZE_Y; j++)
					if (map_item[i][j] & !BulletMap[i][j]) qu.push(vec3{ i, j, 8 });
			int res = BFSNextPos(qu, 1);
			if (res < 9) {
				res = availableStep[res];
				if (res != 5) {
					checkOpt(btnstate[controlMove[res]], btnstate[controlMove[res]] ^ 1);
					if (AI_DEBUG) printf("\nchange %c\n", controlMove[res]);
				}
			}
			if (res > 4) aiState.status ^= STATUS_FIND, aiState.status |= STATUS_AWAY;
		}
		if (opt) break;
		if (aiState.status & STATUS_AWAY) {
			if (AI_DEBUG) printf("away");
			checkAllPlayer();
			if (sceenPlayers.size() == 0) {
				aiState.status ^= STATUS_AWAY;
				continue;
			}
			if (!inMap(aiState.awayx, aiState.awayy)) aiState.awayx = nowx, aiState.awayy = nowy;
			if (aiState.awayx == nowx && aiState.awayy == nowy) {
				veci fp = findFarestPoint();
				aiState.awayx = fp.x, aiState.awayy = fp.y;
			}
			if (aiState.awayx != nowx || aiState.awayy != nowy) {
				std::queue< vec3 > qu;
				for (int i = -1; i <= 1; i++)
					for (int j = -1; j <= 1; j++)
						if (inMap(aiState.awayx + i, aiState.awayy + j)) qu.push({ aiState.awayx + i , aiState.awayy + j , 8 });
				int res = BFSNextPos(qu, 1);
				if (res < 9) {
					res = availableStep[res];
					if (res != 5) {
						checkOpt(btnstate[controlMove[res]], btnstate[controlMove[res]] ^ 1);
						if (AI_DEBUG) printf("\nchange %c\n", controlMove[res]);
					}
				}
				if (res > 4) {
					aiState.awayx = nowx, aiState.awayy = nowy;
					if (random.rand() % 4 == 0) {
						int randx = random.rand() % 4;
						checkOpt(btnstate[controlMove[randx]], btnstate[controlMove[randx]] ^ 1);
					}
				}
			}
			else if (random.rand() % 4 == 0) {
				int randx = random.rand() % 4;
				checkOpt(btnstate[controlMove[randx]], btnstate[controlMove[randx]] ^ 1);
			}
		}
		if (opt) break;
		if (aiState.status & STATUS_WANDER) {
			if (AI_DEBUG) printf("wander");
			int rc = 0;
			if (!inMap(aiState.gox, aiState.goy)) aiState.gox = nowx, aiState.goy = nowy;
			while (aiState.gox == nowx && aiState.goy == nowy) {
				aiState.gox = aiState.gox + random.rand() % MAP_SIZE_X - MAP_SIZE_X / 2, aiState.goy = aiState.goy + random.rand() % MAP_SIZE_Y - MAP_SIZE_Y / 2;
				if (!inMap(aiState.gox, nowy))aiState.gox = nowx;
				if (!inMap(nowx, aiState.goy))aiState.goy = nowy;
				if (++rc >= RAND_LIMIT) break;
			}
			if (aiState.gox != nowx || aiState.goy != nowy) {
				std::queue< vec3 > qu;
				for (int i = -1; i <= 1; i++)
					for (int j = -1; j <= 1; j++)
						if (inMap(aiState.gox + i, aiState.goy + j)) qu.push({ aiState.gox + i , aiState.goy + j , 8 });
				int res = BFSNextPos(qu, 1);
				if (res < 9) {
					res = availableStep[res];
					if (res != 5) {
						checkOpt(btnstate[controlMove[res]], btnstate[controlMove[res]] ^ 1);
						if (AI_DEBUG) printf("\nchange %c\n", controlMove[res]);
					}
				}
				if (res > 4) {
					aiState.gox = nowx, aiState.goy = nowy;
					if (random.rand() % 4 == 0) {
						int randx = random.rand() % 4;
						checkOpt(btnstate[controlMove[randx]], btnstate[controlMove[randx]] ^ 1);
					}
				}
			}
			else if (random.rand() % 4 == 0) {
				int randx = random.rand() % 4;
				checkOpt(btnstate[controlMove[randx]], btnstate[controlMove[randx]] ^ 1);
			}
		}
	}
	if (AI_DEBUG) printf("***end***");
	return;
}
#endif
/*
	void Game::CiyangAI() {
	// return;
	static Random random(time(0));
	static struct AIState { int lastex, lastey; } ais = { state.p[state.my].pos.x, state.p[state.my].pos.y };
	static struct CYNODE { int x, y, lastt; } nowno;
	int mx = state.p[state.my].pos.x, my = state.p[state.my].pos.y, nx, ny, lastab, flak = 0, clPlayer;
	double mindis = 1e9;
	std::vector< int > scPlayer;
	for (int i = 0; i < state.cnt; i++) {
		if (i == state.my || state.p[i].remove) continue;
		if (abs(state.p[i].pos.x - mx) <= SIGHT_SIZE_X * 1.5 && abs(state.p[i].pos.y - my) <= SIGHT_SIZE_Y * 1.5) scPlayer.push_back(i);
		if (mindis > (state.p[i].pos - state.p[state.my].pos).len()) mindis = (state.p[i].pos - state.p[state.my].pos).len(), clPlayer = i;
	}
	static int arBullet[MAP_SIZE_X][MAP_SIZE_Y], wp[MAP_SIZE_X][MAP_SIZE_Y], moves[][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
	static char movesc[][3] = { "AW", "AA", "AS", "WW", "SS", "DW", "DD", "DS" };
	auto RandNextPos = [mx, my, this](int cnt) -> void {
		while (cnt--) {
			if (inMap(ais.lastex, ais.lastey) && !isWall(ais.lastex, ais.lastey) && (abs(ais.lastex - mx) + abs(ais.lastey - my)) > 4) break;
			ais.lastex += random.rand() % 30 - 15, ais.lastey += random.rand() % 30 - 15;
			ais.lastex = max(0, ais.lastex), ais.lastex = min(ais.lastex, MAP_SIZE_X - 1), ais.lastey = max(0, ais.lastey), ais.lastey = min(ais.lastey, MAP_SIZE_Y - 1);
		}
		return;
	};
	auto BFSNextPos = [mx, my, &nx, &ny, this](std::queue< CYNODE >& qu, int bul) -> int {
		while (!qu.empty()) {
			nowno = qu.front(), qu.pop();
			if (nowno.x == mx && nowno.y == my) return 7 - nowno.lastt;
			for (int i = 0; i < 8; i++) {
				nx = nowno.x + moves[i][0], ny = nowno.y + moves[i][1];
				if (!inMap(nx, ny) || isWall(nx, ny) || wp[nx][ny]) continue;
				if (bul && arBullet[nx][ny]) continue;
				qu.push(CYNODE{ nx, ny, i }), wp[nx][ny] = 1;
			}
		}
		return 8;
	};

	auto BFSRandPos = [this, RandNextPos, BFSNextPos, mx, my, &flak]() -> int {
		RandNextPos(20);
		if (inMap(ais.lastex, ais.lastey) && !isWall(ais.lastex, ais.lastey) && !arBullet[ais.lastex][ais.lastey] && (ais.lastex != mx || ais.lastey != my)) {
			std::queue< CYNODE > qu;
			qu.push(CYNODE{ ais.lastex, ais.lastey, 0 });
			memset(wp, 0, sizeof(wp)), wp[ais.lastex][ais.lastey] = 1;
			int res = BFSNextPos(qu, 1);
			if (res < 8) {
				btnstate['W'] = btnstate['A'] = btnstate['S'] = btnstate['D'] = 0;
				for (int j = 0; j < 2; j++) btnstate[movesc[res][j]] = 1;
				flak = 1;
			}
			if (res == 8) RandNextPos(2);
		}
		return 0;
	};
	memset(arBullet, 0, sizeof(arBullet));
	for (const auto& i : state.l_bt) {
		if (i.playerid == state.my) continue;
		vecd nowb = i.p;
		for (int j = 1; j <= i.base.move_pre_turn; j++) {
			nowb = nowb + i.v;
			if (!inMap(roundx(nowb.x), roundx(nowb.y))) break;
			lastab = arBullet[roundx(nowb.x)][roundx(nowb.y)], arBullet[roundx(nowb.x)][roundx(nowb.y)] = 1;
			if (isWall(roundx(nowb.x), roundx(nowb.y)) && !lastab) break;
		}
	}
	if (lbtn && random.rand() % 2) lbtn = 0;
	if (state.p[state.my].flag_process == PT_RELOAD) btnstate['R'] = 0;
	if (state.p[state.my].flag_process != PT_RELOAD && (state.p[state.my].rest_bullet == 0 || (mindis + 1 > GetPlayerWeapon(state.my).reload_time / 5 && state.p[state.my].rest_bullet < 5))) btnstate['R'] = 1;
	if (state.p[state.my].flag_process == PT_RELOAD || scPlayer.size() <= 1) {
		memset(wp, 0, sizeof(wp));
		std::queue< CYNODE > qu;
		for (int i = 0; i < MAP_SIZE_X; i++)
			for (int j = 0; j < MAP_SIZE_Y; j++)
				if (map_item[i][j] && !arBullet[i][j]) qu.push(CYNODE{ i, j, -1 }), wp[i][j] = 1;
		int res = BFSNextPos(qu, 1);
		if (res < 8) {
			btnstate['W'] = btnstate['A'] = btnstate['S'] = btnstate['D'] = 0;
			for (int j = 0; j < 2; j++) btnstate[movesc[res][j]] = 1;
			flak = 1;
		}
	}
	if (scPlayer.size() == 0) {
		if (!flak) BFSRandPos();
	} else if (scPlayer.size() == 1) {
		veci lastm = mouse_pos;
		if (!lbtn) lbtn = 1, flak = 1;
		if (random.rand() % 2 == 0) flak = 1, mouse_pos = state.p[clPlayer].pos - state.p[state.my].pos + veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2) + veci(random.rand() % 2 - 1, random.rand() % 2 - 1);
		for (vecd bp = state.p[state.my].pos, bv = getv(state.p[state.my].pos, state.p[state.my].pos + (mouse_pos - veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2))); (bp - state.p[state.my].pos).len() < mindis && inMap(roundx(bp.x), roundx(bp.y));
			bp = bp + bv) {
			if (isWall(roundx(bp.x), roundx(bp.y)) && random.rand() % 3 == 0) {
				lbtn = 0, mouse_pos = lastm, flak = 0;
				break;
			}
		}
		if (!flak || random.rand() % 5 == 0) BFSRandPos();
	} else {
		if (lbtn && random.rand() % 2) mouse_pos = state.p[clPlayer].pos - state.p[state.my].pos + veci(SIGHT_SIZE_X / 2, SIGHT_SIZE_Y / 2) + veci(random.rand() % 2 - 1, random.rand() % 2 - 1);
		if (random.rand() % 2 && !lbtn) lbtn = 1, flak = 1;
		if (!flak || random.rand() % 10 == 0) BFSRandPos();
	}
	return;
}
*/