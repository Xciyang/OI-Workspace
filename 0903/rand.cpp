#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
int t, n;
char tmps[100], canc[]= "0123456789,";
int main() {
	srand(time(0));
	t= 10;
	printf("%d\n", t);
	while(t--) {
		n= rand() % 10 + 30;
		for(int i= 0; i < n; i++) putchar(rand() % 3 ? '?' : canc[rand() % 11]);
		putchar('\n');
	}
	return 0;
}