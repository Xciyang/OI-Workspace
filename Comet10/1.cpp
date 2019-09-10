#include <iostream>
#include <stdio.h>
using namespace std;
int n, cnt;
string s;
int main() {
	cin >> n;
	while(n--) {
		cin >> s;
		s.reserve();
		if(s.size() > 4 && s.substr(s.size() - 5) == "acpty") ++cnt;
	}
	cout << cnt;
	return 0;
}