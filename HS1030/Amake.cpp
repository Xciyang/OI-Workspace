#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
using namespace std;
int main() {
	cout << 1 << endl;
	srand(time(0) + getpid());
	cout << 1ull * rand() * rand() % 100000 + 1 << ' ' << 1ull * rand() * rand() % 100000 + 1 << endl;
	return 0;
}