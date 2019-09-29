#include <iostream>
#include <stdio.h>
using namespace std;
int n, cnt;
int judge(int x) {
	for(int i= 2; i * i <= x; i++)
		if(x % i == 0) return 0;
	return 1;
}
int main() {
	cin >> n;
	printf("%.12lf\n", (double)(n / 2 + n % 2) / n);
	return 0;
}