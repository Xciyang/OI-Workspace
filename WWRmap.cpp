#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
class MapMaker {
#define MINHOUSENUM 9
#define MAXHOUSENUM 15
#define HOUSESIZ 10
#define MINBLOCKSIZ 2
#define MAXBLOCKSIZ 6
#define BLOCKDEN 60
	private:
	int Rand(int l, int r) {
#define rand rand
		return rand() % (r - l + 1) + l;
#undef rand
	}

	public:
	int MAP[500][500], MAPC[500][500];
	MapMaker() {}
	~MapMaker() {}
	void make(int x0, int y0, int x1, int y1) {
		memset(MAP, 0, sizeof(MAP)), memset(MAPC, 0, sizeof(MAPC));
		int cnt= 0, tmpx, tmpy, tmpx2, tmpy2;
		while(cnt < MAXHOUSENUM) {
			tmpx= Rand(x0, x1), tmpy= Rand(y0, y1);
			if(tmpx + HOUSESIZ / 2 > x1 || tmpy + HOUSESIZ / 2 > y1) continue;
			int rsiz= Rand(HOUSESIZ / 2, HOUSESIZ);
			tmpx2= min(tmpx + rsiz, x1), tmpy2= min(tmpy + rsiz, y1);
			int flag= 0;
			for(int i= tmpx; i <= tmpx2 && !flag; i++)
				for(int j= tmpy; j <= tmpy2 && !flag; j++)
					if(MAPC[i][j]) flag= 1;
			if(flag) {
				if(cnt >= MINHOUSENUM && Rand(0, 1)) ++cnt;
				continue;
			}
			for(int i= tmpx; i <= tmpx2; i++)
				for(int j= tmpy; j <= tmpy2; j++) MAPC[i][j]= 1;
			for(int i= tmpx; i <= tmpx2; i++) MAP[i][tmpy]= MAP[i][tmpy2]= 2;
			for(int i= tmpy; i <= tmpy2; i++) MAP[tmpx][i]= MAP[tmpx2][i]= 2;
			if(Rand(0, 2)) MAP[Rand(tmpx + 1, tmpx2 - 1)][tmpy]= 0, flag= 1;
			if(Rand(0, 2)) MAP[Rand(tmpx + 1, tmpx2 - 1)][tmpy2]= 0, flag= 1;
			if(Rand(0, 2)) MAP[tmpx][Rand(tmpy + 1, tmpy2 - 1)]= 0, flag= 1;
			if(Rand(0, 2)) MAP[tmpx2][Rand(tmpy + 1, tmpy2 - 1)]= 0, flag= 1;
			if(!flag) {
				MAP[Rand(tmpx + 1, tmpx2 - 1)][tmpy]= 0;
				MAP[Rand(tmpx + 1, tmpx2 - 1)][tmpy2]= 0;
				MAP[tmpx][Rand(tmpy + 1, tmpy2 - 1)]= 0;
				MAP[tmpx2][Rand(tmpy + 1, tmpy2 - 1)]= 0;
			}
			++cnt;
		}
		for(int k= 1; k <= BLOCKDEN; k++) {
			tmpx= Rand(x0, x1), tmpy= Rand(y0, y1);
			if(tmpx + MINBLOCKSIZ > x1 || tmpy + MINBLOCKSIZ > y1) continue;
			tmpx2= tmpx + Rand(MINBLOCKSIZ, MAXBLOCKSIZ), tmpy2= tmpy + Rand(MINBLOCKSIZ, MAXBLOCKSIZ);
			int flag= 0, ic= Rand(1, 2);
			for(int i= tmpx; i <= tmpx2 && !flag; i++)
				for(int j= tmpy; j <= tmpy2 && !flag; j++)
					if(MAP[i][j] || MAPC[i][j]) flag= 1;
			if(flag) continue;
			for(int i= tmpx; i <= tmpx2; i++)
				for(int j= tmpy; j <= tmpy2; j++) MAPC[i][j]= MAP[i][j]= ic;
		}
		return;
	}
#undef HOUSENUM
#undef HOUSESIZ

#undef WALLBLOCK
#undef WALLBDEN
};
int main() {
	srand(time(0));
	freopen("a.txt", "w", stdout);
	MapMaker mak;
	mak.make(1, 1, 100, 100);
	for(int i= 1; i <= 100; i++) {
		for(int j= 1; j <= 100; j++) {
			cout << mak.MAP[i][j];
		}
		cout << endl;
	}
	return 0;
}