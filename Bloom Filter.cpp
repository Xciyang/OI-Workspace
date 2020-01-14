#include <iostream>
#include <stdio.h>
#include <map>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int bukmax = 10000;
int n, k, num[101], buk[bukmax + 5], mods[101][2], tmpp[101];
map< string, bool > mm;
char str[101];
void maker(int l, int x, int y, int z) {
	num[0] = x % 10, num[1] = y % 10;
	for(int i = 2; i < l; i++) num[i] = (num[i - 2] * x + num[i - 1] * y + z) % 10;
	return;
}
void init(int kk) {
	k = kk;
	for(int i = 1; i <= k; i++) mods[i][0] = rand() + 1, mods[i][1] = rand() % bukmax + 1;
	return;
}
bool judge1(int l) {
	for(int i = 1; i <= k; i++) tmpp[i] = 0;
	for(int i = 0; i < l; i++)
		for(int j = 1; j <= k; j++) tmpp[j] = (tmpp[j] * mods[j][0] + num[i]) % mods[j][1];
	int flg = 1;
	for(int i = 1; i <= k; i++) {
		if(!buk[tmpp[i]]) {
			flg = 0;
			break;
		}
	}
	for(int i = 1; i <= k; i++) buk[tmpp[i]] = 1;
	return flg;
}
bool judge2(int l) {
	for(int i = 0; i < l; i++) str[i] = num[i] + '0';
	str[l] = 0;
	int flg = mm[str];
	mm[str] = 1;
	return flg;
}
int main() {
	srand(time(0));
	init(100);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		int l = rand() % 91 + 10, x = rand() + 1, y = rand() + 1, z = rand() + 1;
		maker(l, x, y, z);
		int res1 = judge1(l), res2 = judge2(l);
		if(res1 != res2) {
			cout << res1 << ' ' << res2 << endl;
			cout << str << endl;
			cout << "err" << endl;
		}
	}
	return 0;
}