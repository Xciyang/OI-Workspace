#include <iostream>
#include <stdio.h>
#include <map>
using namespace std;
int n, q;
map< string, string > mm;
string tmps, tmps2;
int main() {
	cin >> n >> q;
	for(int i= 1; i <= n; i++) {
		cin >> tmps >> tmps2;
		mm[tmps]= tmps2;
	}
	for(int i= 1; i <= q; i++) {
		cin >> tmps;
		for(int j= 0; j < 4; j++) {
			cin >> tmps2;
			if(mm[tmps] == tmps2) cout << char('A' + j) << endl;
		}
	}
	return 0;
}