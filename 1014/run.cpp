#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int c;
int n;
#define FNAME "1"
#define RND "rand"
#define YOU "seq"
#define STD "seqbl"
#define OPENSTD 1
int main() {
	while(true) {
		printf("-begin-\n");
		system(".\\" RND " > ./" FNAME ".in");
		c= clock();
		system(".\\" YOU " < ./" FNAME ".in > ./now.out");
		c= clock() - c;
		printf("YOU TIME: %lf\n", (double)c / CLOCKS_PER_SEC);
#if OPENSTD == 1
		c= clock();
		system(".\\" STD " < ./" FNAME ".in > ./" FNAME ".out");
		c= clock() - c;
		printf("STD TIME: %lf\n", (double)c / CLOCKS_PER_SEC);
		if(system("fc .\\" FNAME ".out .\\now.out")) {
			printf("�����������");
			while(getchar()) break;
		}
#endif
		printf("-end-\n");
	}
	return 0;
}