#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <math.h>
using namespace std;
vector< string > v, v2;
string tmps;
string getstr() {
	string res= "";
	char ch= getchar();
	if(ch == EOF) return res;
	while(ch != '\r' && ch != '\n' && ch != EOF) res+= ch, ch= getchar();
	return res;
}
string getstr2() {
	int flag= 0;
	string res= "";
	char ch= getchar();
	if(ch == EOF) return res;
	while(ch != '\r' && ch != '\n' && ch != EOF) {
		if(ch == '<') {
			if(res.size()) res.pop_back();
			flag= 1;
		}
		else
			res.push_back(ch);
		ch= getchar();
	}
	if(!flag && res == "EOF") return "???";
	string res2= "";
	for(int i= 0; i < res.size(); i++)
		if((res[i] >= 'a' && res[i] <= 'z') || res[i] == '.' || res[i] == ' ') res2+= res[i];
	return res2;
}
long long tot= 0, times;
inline long long round(long long x, long long y) {
	return x * 60 / y + ((x * 60 % y > y / 2) ? 1 : 0);
}
int main() {
	while(true) {
		tmps= getstr2();
		if(tmps == "???") break;
		v.push_back(tmps);
	}
	while(true) {
		tmps= getstr2();
		if(tmps == "???") break;
		v2.push_back(tmps);
	}
	cin >> times;
	for(int i= 0; i < v.size() && i < v2.size(); i++) {
		for(int j= 0; j < v[i].size() && j < v2[i].size(); j++) {
			if(v[i][j] == v2[i][j]) ++tot;
		}
	}
	cout << round(tot * 60.0 / times) << endl;
	return 0;
}