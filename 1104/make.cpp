#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
using namespace std;
int n;
#define FILENAME ".\\data\\T107"
int main() {
	srand(time(0) + getpid());
	while(true) {
		freopen(FILENAME ".in", "w", stdout);
		n= 100000;
		cout << n << endl;
		// for(int i= 2; i <= n; i++) cout << rand() % (i - 1) + 1 << ' ';

		for(int i= 2; i <= n; i++) cout << rand() % (i - i / 2) + i / 2 << ' ';
		cout << endl;
		system("Astd < " FILENAME ".in > " FILENAME ".out");
		system("zhuoer < " FILENAME ".in > zhuoer.out");
		if(system("fc " FILENAME ".out zhuoer.out > fc.out")) {
			printf("123");
		}
	}
	return 0;
}