#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int c;
int n;
#define FNAME "1"
#define RND "Brand"
#define YOU "B"
#define STD "Bbl"
#define OPENSTD 1
int main() {
	while(true) {
		printf("-begin-\n");
		system(".\\" RND " > ./" FNAME ".in");
		c= clock();
		system(".\\" YOU " < ./" FNAME ".in > ./" FNAME ".out");
		c= clock() - c;
		printf("YOU TIME: %lf\n", (double)c / CLOCKS_PER_SEC);
#if OPENSTD == 1
		c= clock();
		system(".\\" STD " < ./" FNAME ".in > ./std.out");
		c= clock() - c;
		printf("STD TIME: %lf\n", (double)c / CLOCKS_PER_SEC);
		if(system("Bcheck")) {
			printf("任意键继续。");
			while(getchar()) break;
		}
#endif
		printf("-end-\n");
	}
	return 0;
}