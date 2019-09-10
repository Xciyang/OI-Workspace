#include <iostream>
#include <stdio.h>
#include <bitset>
using namespace std;
int main() {
	bitset< 16 > num;
	for(int i= 83; i; i= (i - 1) & 83) {
		num= i;
		for(int i= 15; i > -1; i--) putchar('0' + num[i]);
		putchar('\n');
	}
	return 0;
}