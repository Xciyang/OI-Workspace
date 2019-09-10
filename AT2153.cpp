#include <iostream>
#include <stdio.h>
using namespace std;
string str;
int main() {
	cin >> str;
	cout << string(((str[0] == str[str.size() - 1]) ^ (str.size() & 1)) ? "First" : "Second") << endl;
	return 0;
}