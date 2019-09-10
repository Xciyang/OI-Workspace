#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int c;
int n;
#define CAK "3"
int main() {
	while(true) {
		printf("-begin-\n");
		system(".\\rand.exe > ./" CAK ".in");
		c= clock();
		system(".\\2.exe < ./" CAK ".in > ./now.out");
		c= clock() - c;
		printf("MY TIME: %lf\n", (double)c / CLOCKS_PER_SEC);

		c= clock();
		system(".\\2std.exe < ./" CAK ".in > ./" CAK ".out");
		c= clock() - c;
		printf("STD TIME: %lf\n", (double)c / CLOCKS_PER_SEC);
		if(system("fc .\\" CAK ".out .\\now.out")) {
			getchar();
		}
		printf("-end-\n");
	}
	return 0;
}