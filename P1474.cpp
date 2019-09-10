#include <iostream>
#include <stdio.h>
using namespace std;
long long v, n, f[10005], tmpx;
int main() {
	cin >> v >> n, f[0]= 1;
	for(int i= 1, j; i <= v; i++)
		for(cin >> tmpx, j= tmpx; j <= n; j++) f[j]+= f[j - tmpx];
	cout << f[n] << endl;
	return 0;
}