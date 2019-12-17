#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
char s[] = "UIDCS";
int main() {
	srand(time(0));
	for(int i = 0; i < 5; i++) {
		int x = rand() % 100, y = rand() % 99;
		if(x == y) y = y + 1;
		if(x > y) swap(x, y);
		cout << s[rand() % 5] << ' ' << (rand() % 2 ? '(' : '[') << x << ',' << y << (rand() % 2 ? ')' : ']') << endl;
	}
	return 0;
}