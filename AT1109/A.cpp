#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <string.h>
#include <vector>
#include <queue>
#include <map>
using namespace std;
inline int lowb(int x) {
	return x & -x;
}
int n, m/* , a[], b[], p[], ans */;
struct EDGE {
	int to, dis;
};
int main() {
	cin >> n;
	cout << n / 2 - (n + 1) % 2 << endl;
	return 0;
}