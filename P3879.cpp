#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
using namespace std;
int n, l;
map< string, vector< int > > mm;
map< string, bool > m2;
string str;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) {
		cin >> l;
		m2.clear();
		for(int j= 1; j <= l; j++) {
			cin >> str;
			if(m2[str]) continue;
			mm[str].push_back(i);
			m2[str]= 1;
		}
	}
	cin >> n;
	for(int i= 1; i <= n; i++) {
		cin >> str;
		for(int j= 0; j < mm[str].size(); j++) {
			cout << mm[str][j] << ' ';
		}
		cout << endl;
	}
	return 0;
}