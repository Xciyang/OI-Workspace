#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int c;
int n;
#define CAK "CAK10"
int main() {
	while(true) {
		printf("-begin-\n");
		system(".\\0903.exe > ./CAK/" CAK ".in");
		c= clock();
		system(".\\JSB.exe < ./CAK/" CAK ".in > ./CAK/now.out");
		c= clock() - c;
		printf("BAOLI TIME: %lf\n", (double)c / CLOCKS_PER_SEC);

		c= clock();
		system(".\\JSB2.exe < ./CAK/" CAK ".in > ./CAK/" CAK ".out");
		c= clock() - c;
		printf("YOUHUA TIME: %lf\n", (double)c / CLOCKS_PER_SEC);
		system("fc .\\CAK\\" CAK ".out .\\CAK\\now.out");
		printf("-end-\n");
	}
	return 0;
}