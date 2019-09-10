#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;
#define RANDOM_MAX 0x7FFFFFFF

static unsigned long nxt= 1;

void my_srand(unsigned int seed) {
	nxt= seed;
}
int q, cnt, flag[10000000];
int main() {
	string str= "😄";
	wstring stt2= L"😄";
	cout << str << endl;
	wcout << stt2 << endl;

	return 0;
}