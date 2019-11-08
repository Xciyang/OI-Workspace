#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m;
char tmps[100005], tmps2[100005];
int main() {
	cin >> (tmps + 1) >> (tmps2 + 1);
	n= strlen(tmps + 1), m= strlen(tmps2 + 1);
	for(int i= 1; i <= n; i++) {
		for(int j= i, k= 1; j <= n; j++) {
            if(tmps[j] == tmps2[k]) {
                ++k;
            }
		}
	}
	return 0;
}


