#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int n, l[20005], r[20005], F[2][2];
inline int abs(int x) {
	return x < 0 ? -x : x;
}
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> l[i] >> r[i];
	l[0]= r[0]= 1, l[n + 1]= r[n + 1]= n;
	for(int i= 1; i <= n + 1; i++) {
		F[i & 1][0]= min(F[(i & 1) ^ 1][0] + abs(l[i - 1] - r[i]), F[(i & 1) ^ 1][1] + abs(r[i - 1] - r[i])) + r[i] - l[i] + 1;
		F[i & 1][1]= min(F[(i & 1) ^ 1][0] + abs(l[i - 1] - l[i]), F[(i & 1) ^ 1][1] + abs(r[i - 1] - l[i])) + r[i] - l[i] + 1;
	}
	cout << min(F[(n + 1) & 1][0], F[(n + 1) & 1][1]) - 2 << endl;
	return 0;
}