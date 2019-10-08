#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int ans, len, p[30000007], n, mr, mid;
char tmps[30000007], tmps2[11000007];
int main() {
	cin >> tmps2, len= strlen(tmps2);
	tmps[0]= '|';
	for(int i= 0; i < len; i++) tmps[i * 2 + 1]= '|', tmps[i * 2 + 2]= tmps2[i];
	tmps[len * 2 + 1]= '|', n= len * 2;
	for(int i= 1; i < n; i++) {
		if(i < mr)
			p[i]= min(mr - i, p[mid * 2 - i]);
		else
			p[i]= 1;
		while(tmps[i - p[i]] == tmps[i + p[i]]) ++p[i];
		if(i + p[i] - 1 > mr) mr= i + p[i] - 1, mid= i;
		ans= max(ans, p[i] - 1);
	}
	cout << ans << endl;
	return 0;
}