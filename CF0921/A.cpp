#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
int n, len, ans;
char tmps[200005];
int main() {
	cin >> n >> tmps;
	len= strlen(tmps);
	for(int i= 0; i < len; i+= 2)
		if(tmps[i] == tmps[i + 1]) ++ans, tmps[i]= (tmps[i] == 'a' ? 'b' : 'a');
	cout << ans << endl << tmps << endl;
	return 0;
}