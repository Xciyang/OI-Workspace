#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
char xunh[256];
int main() {
	srand(time(0));
	xunh[0]= 'A' + rand() % 26;
	for(int i= 0; i < 20; i++) {
		if(!xunh[i]) {
			xunh[i]= 'A' + rand() % 26;
			if(rand() % 2) {
				for(int j= rand() % i, l= i; j < i && l < 20; j++, l++) xunh[l]= xunh[j];
			}
		}
		putchar(xunh[i]);
	}
	return 0;
}