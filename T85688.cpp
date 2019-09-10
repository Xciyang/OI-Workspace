#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#pragma GCC optimize(3)

using namespace std;
namespace Mker {
//  Powered By Kawashiro_Nitori
//  Made In Gensokyo, Nihon
#define uint unsigned int
uint sd;
int op;
inline void init() {
	scanf("%u %d", &sd, &op);
}
inline uint uint_rand() {
	sd^= sd << 13;
	sd^= sd >> 7;
	sd^= sd << 11;
	return sd;
}
inline double get_n() {
	double x= (double)(uint_rand() % 100000) / 100000;
	return x + 4;
}
inline double get_k() {
	double x= (double)(uint_rand() % 100000) / 100000;
	return (x + 1) * 5;
}
inline void read(double &n, double &a, double &b) {
	n= get_n();
	a= get_k();
	if(op)
		b= a;
	else
		b= get_k();
}
}  // namespace Mker
int t, pown, tmppown;
double ans, bestmin, bestmax, n, a, b, tmp1, tmp2;
void SA() {
	pown= pow(n, a) + pow(n, b);
	bestmin= bestmax= n;
	for(double T= 1; T > 1e-8;) {
		tmp1= bestmin - T, tmppown= pow(tmp1, a) + pow(tmp1, b);
		if(tmppown == pown)
			bestmin= tmp1;
		else
			T*= 0.05;
	}
	for(double T= 1; T > 1e-8;) {
		tmp2= bestmax + T, tmppown= pow(tmp2, a) + pow(tmp2, b);
		if(tmppown == pown)
			bestmax= tmp2;
		else
			T*= 0.05;
	}

	return;
}
int main() {
	srand(time(0)), scanf("%d", &t), Mker::init();
	while(t--) {
		Mker::read(n, a, b);
		SA();
		ans+= bestmax - bestmin;
	}
	printf("%.5lf\n", ans);
	return 0;
}