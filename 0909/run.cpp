#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int c;
int n;
#define FN "1766"
int main() {
	while(true) {
		printf("-begin-\n");
		system(".\\1766rand.exe > ./" FN ".in");
		c= clock();
		system(".\\1766STD.exe < ./" FN ".in > ./now.out");
		c= clock() - c;
		printf("STD TIME: %lf\n", (double)c / CLOCKS_PER_SEC);

		c= clock();
		system(".\\1766.exe < ./" FN ".in > ./" FN ".out");
		c= clock() - c;
		printf("MY TIME: %lf\n", (double)c / CLOCKS_PER_SEC);
		if(system("fc .\\" FN ".out .\\now.out")){
			getchar();
		}
		printf("-end-\n");
	}
	return 0;
}