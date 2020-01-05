#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <queue>
using namespace std;
int main() {
	srand(time(0));
	int n = 2000;
	cout << n << endl;
	for(int i = 1; i <= n; i++) cout << rand() % (n / 3) + 1 << ' ';
	cout << endl;
	return 0;
}