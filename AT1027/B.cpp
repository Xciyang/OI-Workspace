#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <queue>
using namespace std;
int n, a[15], flag;
int main() {
	cin >> n;
	for(int i= 1; i <= 9; i++)
		for(int j= 1; j <= 9; j++) flag|= (i * j == n);
	cout << (flag ? "Yes" : "No") << endl;
	return 0;
}