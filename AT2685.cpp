#include <iostream>
#include <stdio.h>
using namespace std;
string str;
int main() {
    cin >> str;
    cout << str[0] << str.size() - 2 << str[str.size() - 1] << endl;
	return 0;
}