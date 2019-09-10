#include <iostream>
#include <stdio.h>
#include <string.h>
#define int long long
using namespace std;
int n, m[3][3]= {{0, 0, 0}, {0, 1, 1}, {0, 1, 0}};
int ans[3][3]= {{0, 0, 0}, {0, 1, 0}, {0, 0, 1}};
int tmp[3][3];
void mul1() {
	memset(tmp, 0, sizeof(tmp));
	for(int i= 1; i <= 2; i++)
		for(int j= 1; j <= 2; j++)
			for(int k= 1; k <= 2; k++) tmp[i][k]= (tmp[i][k] + m[i][j] * ans[j][k]) % 1000000007;
	for(int i= 1; i <= 2; i++)
		for(int j= 1; j <= 2; j++) ans[i][j]= tmp[i][j];
	return;
}
void mul2() {
	memset(tmp, 0, sizeof(tmp));
	for(int i= 1; i <= 2; i++)
		for(int j= 1; j <= 2; j++)
			for(int k= 1; k <= 2; k++) tmp[i][k]= (tmp[i][k] + m[i][j] * m[j][k]) % 1000000007;
	for(int i= 1; i <= 2; i++)
		for(int j= 1; j <= 2; j++) m[i][j]= tmp[i][j];
	return;
}
signed main() {
	cin >> n;
	if(n <= 2) {
		cout << 1 << endl;
		return 0;
	}
	n-= 2;
	while(n) {
		if(n & 1) mul1();
		mul2();
		n>>= 1;
	}
	cout << (ans[1][1] + ans[2][1]) % 1000000007 << endl;
	return 0;
}