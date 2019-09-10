#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
char str[100005], str2[100005];
char zh(char ch) {
	switch(ch) {
		case 'b': return 'd';
		case 'd': return 'b';
		case 'p': return 'q';
		case 'q': return 'p';
		default: break;
	}
	return ch;
}
int main() {
	cin >> str;
	int len= strlen(str);
	for(int i= 0; i < len; i++) str2[len - i - 1]= zh(str[i]);
	cout << string(strcmp(str, str2) == 0 ? "Yes" : "No") << endl;
	return 0;
}