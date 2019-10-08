#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
char str1[1005], str2[1005];
int len1, len2;
char changeb(char m, char y) {
	return (((m - (m >= 'A' && m <= 'Z' ? 'A' : 'a')) - (y - (y >= 'A' && y <= 'Z' ? 'A' : 'a'))) % 26 + 26) % 26 + (m >= 'A' && m <= 'Z' ? 'A' : 'a');
}
int main() {
	cin >> str1 >> str2;
	len1= strlen(str1), len2= strlen(str2);
	for(int i= 0; i < len2; i++) putchar(changeb(str2[i], str1[i % len1]));
	putchar('\n');
	return 0;
}