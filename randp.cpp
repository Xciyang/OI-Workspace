#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int DAY_SUM= 20;
const int PEP_SUM= 12;
struct DAY {
	int t1, t2, t3;
} d[DAY_SUM + 1];
int sum[PEP_SUM + 1];
int absi(int x) {
	return x < 0 ? -x : x;
}
int main() {
	srand(time(0));
	int ch;
	for(int i= 1; i <= DAY_SUM; i++) {
		int x= rand() % PEP_SUM + 1;
		while(sum[x] >= DAY_SUM * 3 / PEP_SUM) x= rand() % PEP_SUM + 1;
		int y= rand() % PEP_SUM + 1, by= 0x3f3f3f3f;
		ch= clock();
		while(clock() - ch < CLOCKS_PER_SEC * 0.5) {
			while(x == y || sum[y] >= DAY_SUM * 3 / PEP_SUM) y= rand() % PEP_SUM + 1;
			if(absi(x - by) > absi(x - y)) by= y;
		}
		y= by;
		int z= rand() % PEP_SUM + 1, bz= 0x3f3f3f3f;
		ch= clock();
		while(clock() - ch < CLOCKS_PER_SEC * 0.5) {
			while(x == z || y == z || sum[z] >= DAY_SUM * 3 / PEP_SUM) z= rand() % PEP_SUM + 1;
			if(absi(y - bz) > absi(y - z)) bz= z;
		}
		z= bz;
		++sum[x], ++sum[y], ++sum[z];
		d[i].t1= x, d[i].t1= y, d[i].t3= z;
		cout << x << ' ' << y << ' ' << z << endl;
	}
	return 0;
}