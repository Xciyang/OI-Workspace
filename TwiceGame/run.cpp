#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int c;
int n;
#define FNAME "1"
#define RND "rand"
#define YOU "main"
#define STD "mainbl"
#define OPENSTD 1
#define MAXTIME 1.0
int main() {
	while(true) {
		printf("-begin-\n");
		system(".\\" RND " > ./" FNAME ".in");
		c= clock();
		system(".\\" YOU " < ./" FNAME ".in > ./now.out");
		c= clock() - c;
		printf("YOU TIME: %lf\n", (double)c / CLOCKS_PER_SEC);
		if(c > MAXTIME * CLOCKS_PER_SEC) {
			printf("任意键继续。");
			while(getchar()) break;
		}
#if OPENSTD == 1
		c= clock();
		system(".\\" STD " < ./" FNAME ".in > ./" FNAME ".out");
		c= clock() - c;
		printf("STD TIME: %lf\n", (double)c / CLOCKS_PER_SEC);
		if(system("fc .\\" FNAME ".out .\\now.out")) {
			printf("任意键继续。");
			while(getchar()) break;
		}
#endif
		printf("-end-\n");
	}
	return 0;
}