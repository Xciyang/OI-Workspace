#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <fstream>
#include <map>
using namespace std;
map< long long, int > mm;
long long randd() {
	return (long long)rand() * rand() % INT_MAX * (rand() * rand() % INT_MAX);
}
const int beginx= 31;
char tmps[256];
int main() {
	srand(time(0));
	for(int i= 0; i < 10; i++) {
		sprintf(tmps, "./data/%d.in", beginx + i);
		ofstream fs;
		fs.open(tmps);
		long long x= randd() % (long long)1e17 + 9e17;
        while(mm[x]) x= randd() % (long long)1e17 + 9e17;
		fs << x << endl;
        mm[x]= 1;
		fs.close();
	}

	return 0;
}