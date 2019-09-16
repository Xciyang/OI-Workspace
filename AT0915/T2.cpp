#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, ok[2][256];
char st[101];
int main() {
	cin >> (st + 1), n= strlen(st + 1);
	ok[1]['R']= ok[1]['U']= ok[1]['D']= 1;
	ok[0]['L']= ok[0]['U']= ok[0]['D']= 1;
	for(int i= 1; i <= n; i++) {
		if(!ok[i % 2][st[i]]) {
			cout << "No" << endl;
			return 0;
		}
	}
    cout << "Yes" << endl;
	return 0;
}