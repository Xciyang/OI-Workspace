#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <queue>
using namespace std;
int main() {
	while(true) {
		system("Bmk.exe > B.in");
		int ch1 = clock();
		system("Bbl.exe < B.in > Bbl.out");
		int ch2 = clock();
		cout << "Baoli:" << ch2 - ch1 << endl;
		int ch3 = clock();
		system("B.exe < B.in > B.out");
		int ch4 = clock();
		cout << "B:" << ch4 - ch3 << endl;
		if(system("fc B.out Bbl.out")) {
			cout << "ERROR" << endl;
			system("pause");
		}
	}
	return 0;
}