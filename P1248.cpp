#include <iostream>
#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;
int n;
struct NODE {
	int a, b;
	inline int operator<(const NODE &n2) const {
		return a == n2.a ? b > n2.b : a < n2.a;
	}
} no[1005];
int main() {
	return 0;
}