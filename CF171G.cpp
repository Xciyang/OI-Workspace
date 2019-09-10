#include <iostream>
#include <stdio.h>
using namespace std;
int a3,f[22];
int main() {
    cin >> f[0] >> f[1] >> a3;
    for(int i= 2; i <= a3; i++) f[i]= f[i - 1] + f[i - 2];
	cout << f[a3] << endl;
    return 0;
}