#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int main() {
	while(true) {
		system("P5568make > P5568.in");
		system("P5568 < P5568.in > P5568.out");
		system("P5568std < P5568.in > P5568std.out");
		if(system("fc P5568.out P5568std.out")) {
			cout << -1;
			while(getchar() != '\n') getchar();
		}
	}
	return 0;
}