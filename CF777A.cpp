#include <iostream>
#include <stdio.h>
using namespace std;
int n, x;
int nows[][3]= {{0, 1, 2}, {1, 0, 2}, {1, 2, 0}, {2, 1, 0}, {2, 0, 1}, {0, 2, 1}, {0, 1, 2}};
int main() {
	cin >> n >> x;
	cout << nows[n % 6][x] << endl;
	return 0;
}