#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <math.h>
using namespace std;
vector< string > v, v2;
string tmps;
string getstr() {
	char ch= getchar();
	if(ch == EOF) return "";
	string res= "";
	while(ch != '\r' && ch != '\n' && ch != EOF) res+= ch, ch= getchar();
	return res;
}
int cp[100005];
string getstr2(int x) {
	char ch= getchar();
	if(ch == EOF) return "";
	int flag= 0;
	string res= "";
	while(ch != '\r' && ch != '\n' && ch != EOF) {
		if(ch == '<') {
			if(res.size()) {
				for(int i= (int)res.size() - 1; i >= 0; i--) {
					if(res[i] >= 'a' && res[i] <= 'z') {
						res= res.substr(0, i) + res.substr(i + 1);
						break;
					}
				}
			}
			flag= 1;
		}
		else
			res.push_back(ch);
		if(x < v.size() && res.size())
			if(res[res.size() - 1] == v[x][res.size() - 1]) cp[res.size() - 1]= x;
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
		tmps= getstr();
		if(tmps == "EOF") break;
		v.push_back(tmps);
	}
	memset(cp, 0x3f, sizeof(cp));
	int x= 0;
	while(true) {
		tmps= getstr2(x);
		if(tmps == "???") break;
		v2.push_back(tmps);
		if(x < v.size())
			for(int i= 0; i < v[x].size(); i++) tot+= (cp[i] == x);
		++x;
	}
	cin >> times;
	// for(int i= 0; i < v.size() && i < v2.size(); i++) {
	// 	for(int j= 0; j < v[i].size() && j < v2[i].size(); j++) {
	// 		if(v[i][j] == v2[i][j]) ++tot;
	// 	}
	// }
	cout << round(tot * 60.0 / times) << endl;
	return 0;
}