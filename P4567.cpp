#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
vector< int > v, strr;
int n, k, tmpx;
char str[8];
int main() {
	cin >> n;
	while(n--) {
		cin >> str;
		switch(str[0]) {
			case 'M': cin >> k; break;
			case 'I':
				cin >> tmpx, getchar();
				strr.resize(tmpx);
				for(int i = 0; i < tmpx; i++) strr[i] = getchar();
				v.insert(v.begin() + k, strr.begin(), strr.end());
				break;
			case 'D':
				cin >> tmpx;
				v.erase(v.begin() + k, v.begin() + k + tmpx);
				break;
			case 'R':
				cin >> tmpx;
				strr.resize(tmpx);
				for(int i = 0; i < tmpx; i++) strr[i] = v[k + i];
				for(int i = 0, j = k + tmpx - 1; i < tmpx; i++, j--) v[j] = strr[i];
				break;
			case 'G':
				putchar(v[k]);
				if(v[k] != '\n') putchar('\n');
				break;
			case 'P': --k; break;
			case 'N': ++k; break;
			default: break;
		}
	}
	return 0;
}