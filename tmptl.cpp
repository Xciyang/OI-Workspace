#include <iostream>
#include <stdio.h>
#include <map>
using namespace std;
map< int, int > m[2];
int n, tmpx;
int main() {
	int x = 0;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> tmpx;
		m[x ^ 1][tmpx] = 1;
		for(auto p = m[x].begin(); p != m[x].end(); ++p) {
			m[x ^ 1][p->first + tmpx] = 1;
			m[x ^ 1][p->first] = 1;
		}
		x ^= 1;
	}
	cout << m[x][0] << endl;
	return 0;
}