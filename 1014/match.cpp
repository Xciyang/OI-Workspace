#include <iostream>
#include <stdio.h>
using namespace std;
int n, a, b;
long long f[1000006];
int main() {
	cin >> n >> a >> b;
	f[1]= 1;
	for(int i= 2; i <= n; i++) f[i]= (f[i - 1] * f[i - 1] + 2) % 998244353;
    
	return 0;
}