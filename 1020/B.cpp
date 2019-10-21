#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
int n;
char tmps[1000006], res1[1000006], res2[1000006], latz;
int main() {
	srand(time(0));
	cin >> (tmps + 1);
	n= strlen(tmps + 1);
	latz= 'Z';
	for(int i= n; i; i--) {
		if(tmps[i] == 'Z') {
			if(latz != 'Z') {
				cout << -1 << endl;
				return 0;
			}
			res1[i]= res2[i]= rand() % 10 + '0';
		}
		if(tmps[i] == 'X') {
			res1[i]= rand() % 5 + '5';
			res2[i]= rand() % 5 + '0';
		}
		if(tmps[i] == 'Y') {
			res2[i]= rand() % 5 + '5';
			res1[i]= rand() % 5 + '0';
		}
        latz= tmps[i];
	}
	cout << (res1 + 1) << endl << (res2 + 1) << endl;
	return 0;
}