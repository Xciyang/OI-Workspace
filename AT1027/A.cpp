#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <queue>
using namespace std;
int a, b, ans;
int main() {
	cin >> a >> b;
	if(a < 1 || b < 1 || a > 9 || b > 9) {
		cout << -1 << endl;
		return 0;
	}
	cout << a * b << endl;
	return 0;
}