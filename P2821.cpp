#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
char num[1000005], ans[1000005], endans[1000005];
int len, aptr;
int ZC(int x) {
	int now= 0;
	for(int i= 1; i <= len; i++) {
		now= now * 10 + num[i] - '0';
		ans[i]= '0' + now / x, now%= x;
	}
	return now == 0;
}
void CY() {
	int now= 0, ck= 1;
	while(ck <= len && ans[ck] == '0') ++ck;
	len= len - ck + 1;
	for(int i= 1; i <= len; i++) num[i]= ans[i + ck - 1];
	return;
}
int main() {
	cin >> (ans + 1), len= strlen(ans + 1), CY();
	if(len == 1) {
		cout << (num + 1) << endl;
		return 0;
	}
	for(int i= 9; i >= 2; i--) {
		while(ZC(i)) CY(), endans[++aptr]= '0' + i;
	}
	if(len != 1) {
		cout << "There is no such number!" << endl;
		return 0;
	}
	sort(endans + 1, endans + aptr + 1);
	cout << endans + 1 << endl;
	return 0;
}
