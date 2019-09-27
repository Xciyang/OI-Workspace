#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int c, n;
#define FNAME "TG10"
#define RND "rand"
#define YOU "main"
#define MAXTIME 1.0
int main() {
	printf("-begin-\n");
	system(".\\" RND " > ./" FNAME ".in");
	c= clock();
	system(".\\" YOU " < ./" FNAME ".in > ./" FNAME ".out");
	c= clock() - c;
	printf("YOU TIME: %lf\n", (double)c / CLOCKS_PER_SEC);
	if(c > MAXTIME * CLOCKS_PER_SEC) {
		printf("任意键继续。");
		while(getchar()) break;
	}
	printf("-end-\n");
	return 0;
}