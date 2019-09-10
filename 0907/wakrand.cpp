#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
int n;
long long randd() {
	return (long long)rand() * rand() % INT_MAX * (rand() * rand() % INT_MAX);
}
int main() {
    srand(time(0));
	n= 1000;
    cout << n <<endl;
    for(int i= 1; i < n; i++) 
        cout << i << ' ' << rand() % (n - i) + i + 1 << ' ' << rand() % (int)1e6 << endl;
	return 0;
}