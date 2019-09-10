#include <iostream>
#include <stdio.h>
#include <string.h>

#ifndef ONLINE_JUDGE
#pragma warning(disable : 4996)
#endif
using namespace std;
char num[10][7][6]= {
	{"xxxxx", "x...x", "x...x", "x...x", "x...x", "x...x", "xxxxx"},
	{"....x", "....x", "....x", "....x", "....x", "....x", "....x"},
	{"xxxxx", "....x", "....x", "xxxxx", "x....", "x....", "xxxxx"},
	{"xxxxx", "....x", "....x", "xxxxx", "....x", "....x", "xxxxx"},
	{"x...x", "x...x", "x...x", "xxxxx", "....x", "....x", "....x"},
	{"xxxxx", "x....", "x....", "xxxxx", "....x", "....x", "xxxxx"},
	{"xxxxx", "x....", "x....", "xxxxx", "x...x", "x...x", "xxxxx"},
	{"xxxxx", "....x", "....x", "....x", "....x", "....x", "....x"},
	{"xxxxx", "x...x", "x...x", "xxxxx", "x...x", "x...x", "xxxxx"},
	{"xxxxx", "x...x", "x...x", "xxxxx", "....x", "....x", "xxxxx"},
};
char input[7][1024];
int len, a, b, p, res;
int recognize(int beginx) {
	for(int i= 0; i < 10; i++) {
		for(int j= 0; j < 7; j++) {
			for(int k= 0; k < 5; k++) {
				if(input[j][beginx + k] != num[i][j][k]) goto failed;
			}
		}
		return i;
	failed:;
	}
	return -1;
}
int ans[21];
void putans() {
	for(int i= 0; i < 7; i++) {
		for(int j= p; j; j--) {
			if(j != p) putchar('.');
			for(int k= 0; k < 5; k++) {
				putchar(num[ans[j]][i][k]);
			}
		}
		putchar('\n');
	}
	return;
}
int main() {
	for(int i= 0; i < 7; i++) scanf("%s", input[i]);
	len= (int)strlen(input[0]);
	for(p= 0; p < len; p+= 6) {
		res= recognize(p);
		if(res == -1) break;
		a= a * 10 + res;
	}
	for(p= p + 6; p < len; p+= 6) {
		res= recognize(p);
		b= b * 10 + res;
	}
	a= a + b, p= 0;
	while(a) ans[++p]= a % 10, a/= 10;
	if(!p) ans[++p]= 0;
	putans();
	return 0;
}
/*


*/
