#include <iostream>
#include <stdio.h>
#include <map>
using namespace std;
map< string, string > mm;
string st;
int main() {
	mm["Sunny"]= "Cloudy", mm["Cloudy"]= "Rainy", mm["Rainy"]= "Sunny";
	cin >> st;
	cout << mm[st] << endl;
	return 0;
}