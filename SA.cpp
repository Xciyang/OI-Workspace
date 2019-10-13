#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;
#define MAP_SIZE_X 500
#define MAP_SIZE_Y 500
int n;
struct veci {
	int x, y;
	veci(int x, int y) : x(x), y(x) {}
	veci() {}
	double len() {
		return sqrt(x * x + y * y);
	}
	veci operator-(const veci &v) const {
		return veci(x - v.x, y - v.y);
	}
} pl[10000];
inline int inMap(int x, int y) {
	return x >= 0 && y >= 0 && x < MAP_SIZE_X && y < MAP_SIZE_Y;
}
int main() {
	static const int SA_TIMES= 2;
	static const double SA_BEGIN= (MAP_SIZE_X + MAP_SIZE_Y) * 2;
	static const double SA_END= 1e-6;
	static const double SA_SPEED= 0.95;

	srand(time(0));
	for(int i= 0; i < 100; i++) pl[i].x= rand() % MAP_SIZE_X, pl[i].y= rand() % MAP_SIZE_Y;
	int nowx= rand() % MAP_SIZE_X, nowy= rand() % MAP_SIZE_Y;
	auto calc= [&](int x, int y) -> double {
		double sumc= 1e19;
		for(int i= 0; i < 100; i++) sumc= min(sumc, (pl[i] - veci(x, y)).len());
		return sumc;
	};
	auto findFarestPoint= [&]() -> veci {
		int bestx= nowx, besty= nowy;
		auto Rand= []() -> double { return (double)(rand() % 0x7f) / 0x7f; };
		double bestres= calc(bestx, besty);
		int times= 0;
		while(++times < SA_TIMES) {
			int sax= nowx, say= nowy, sares= calc(bestx, besty);
			for(double T= SA_BEGIN; T > SA_END; T*= SA_SPEED) {
				int nxtx= sax + T * (Rand() - 0.5), nxty= say + T * (Rand() - 0.5);
				while(!inMap(nxtx, nxty)) nxtx= sax + T * (Rand() - 0.5), nxty= say + T * (Rand() - 0.5);
				double tmpres= calc(nxtx, nxty);
				if(tmpres >= bestres) bestres= tmpres, bestx= nxtx, besty= nxty;
				if(tmpres >= sares)
					sares= tmpres, sax= nxtx, say= nxty;
				else if(Rand() < exp((tmpres - sares) / T))
					sax= nxtx, say= nxty;
			}
		}
		return veci(bestx, besty);
	};  // By Simulated Annealing (Unadjusted)

	auto findFarestPointBL= [&]() -> veci {
		veci bestr= veci(nowx, nowy);
		double res= calc(nowx, nowy), tmpres;
		for(int i= 0; i < MAP_SIZE_X; i++) {
			for(int j= 0; j < MAP_SIZE_Y; j++) {
				tmpres= calc(i, j);
				if(tmpres > res) {
					res= tmpres;
					bestr= veci(i, j);
				}
			}
		}
		return bestr;
	};
	int ch= clock();
	veci a= findFarestPoint();
	cout << "SA Times:" << clock() - ch << "ms" << endl;
	cout << a.x << ' ' << a.y << ' ' << calc(a.x, a.y) << endl;
	ch= clock();
	veci b= findFarestPointBL();
	cout << "BL Times:" << clock() - ch << "ms" << endl;
	cout << b.x << ' ' << b.y << ' ' << calc(b.x, b.y) << endl;
	return 0;
}