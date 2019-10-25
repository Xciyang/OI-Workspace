#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
using namespace std;
int Init() {
	srand(time(0) + getpid());
	return 1;
}
const int init= Init();
template < typename T >
T randomByRange(const T &l, const T &r) {
	return T((double)rand() / RAND_MAX * (r - l) + l);
}
char tmpn[4005], tmpm[4005];
int main() {
	int n= randomByRange(7, 10), m= randomByRange(7, 10);
	cout << n << ' ' << m << endl;
	for(int i= 1; i <= n; i++) tmpn[i]= rand() % 2 + '0';
	for(int i= 1, j= 1; i <= m; i++) {
		if(rand() % 2 && j < n) ++j;
		tmpm[i]= rand() % 2 ? rand() % 2 + '0' : tmpn[j];
	}
	cout << (tmpn + 1) << endl << (tmpm + 1) << endl;

	return 0;
}