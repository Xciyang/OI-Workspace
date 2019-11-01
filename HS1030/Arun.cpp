#include <iostream>
#include <stdio.h>
#include <windows.h>
using namespace std;
int main() {
	while(true) {
		system(".\\Amake > ./A.in");
		system(".\\A < ./A.in > ./A.out");
		system(".\\Astd < ./A.in > ./Astd.out");
		if(system("fc .\\A.out .\\Astd.out")) {
			MessageBoxA(NULL, "error", "error", 0);
		}
	}
	return 0;
}