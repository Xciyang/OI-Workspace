#include <iostream>
#include <stdio.h>
#include <stack>
using namespace std;
struct NODE {
	char ch;
	int p;
};
string str;
int vis[1000006], len, ar, al, tmpt;
stack< NODE > ch;

int main() {
	cin >> str, len= str.size();
	for(int i= 0; i < len; i++) {
		if(!ch.empty() && ((str[i] == ')' && ch.top().ch == '(') || (str[i] == ']' && ch.top().ch == '[')))
			vis[i]= vis[ch.top().p]= 1, ch.pop();
		else
			ch.push(NODE{str[i], i});
	}
	al= 1;
	for(int i= 0; i < len; i++) {
		if(!vis[i])
			tmpt= 0;
		else if(++tmpt > ar - al + 1)
			ar= i, al= i - tmpt + 1;
	}
	for(int i= al; i <= ar; i++) putchar(str[i]);
	return 0;
}