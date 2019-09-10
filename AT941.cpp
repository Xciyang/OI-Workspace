#include <iostream>
#include <stdio.h>
using namespace std;
int n, a, b;
int main() {
	cin >> n >> a >> b;
	n%= (a + b);
	if(n <= a && n != 0)
		printf("Ant\n");
	else
		printf("Bug\n");
	return 0;
}