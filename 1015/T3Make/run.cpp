#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int c;
int n;
char tmps[256], tmps2[256], opt[256];
int main() {
	for(int i= 1; i <= 40; i++) {
		printf("-begin-\n");
		sprintf(tmps, ".\\data\\%d.in", i);
		sprintf(tmps2, ".\\data\\%d.out", i);
		sprintf(opt, ".\\std1 < %s > ./now.out", tmps);

		c= clock();
		system(opt);
		c= clock() - c;
		printf("STD1 TIME: %lf\n", (double)c / CLOCKS_PER_SEC);

		sprintf(opt, ".\\std2 < %s > %s", tmps, tmps2);

		c= clock();
		system(opt);
		c= clock() - c;
		printf("STD2 TIME: %lf\n", (double)c / CLOCKS_PER_SEC);
		sprintf(opt, "fc %s .\\now.out", tmps2);
		if(system(opt)) {
			printf("???");
			while(getchar()) break;
		}
		printf("-end-\n");
	}
	return 0;
}