#include <iostream>
#include <stdio.h>
#include <map>
#include <string>
using namespace std;
int n, jz;
string tmps[10][10];
int num[256], vis[10];
int check(int x, const string &st) {
	int len= st.size(), cnt= 0, w[10];
	while(x) w[++cnt]= x % jz, x/= jz;
	if(!cnt) cnt= 1, w[1]= 0;
	if(len != cnt) return 0;
	for(int i= cnt, j= 0; i; i--, j++)
		if(num[st[j]] != w[i]) return 0;
	return 1;
}
void dfs(int nown) {
	if(nown == n) {
		jz= 9;
		while(!vis[jz]) --jz;
		if(!jz) return;
		++jz;
		for(int i= 1; i < n; i++)
			for(int j= 1; j < n; j++)
				if(!check(num[tmps[0][i][0]] + num[tmps[j][0][0]], tmps[j][i])) return;
		for(int i= 1; i < n; i++) cout << tmps[0][i][0] << '=' << num[tmps[0][i][0]] << ' ';
		cout << endl << jz << endl;
		exit(0);
	}
	for(int i= 0; i < 10; i++) {
		if(vis[i]) continue;
		vis[i]= 1;
		num[tmps[0][nown][0]]= i;
		dfs(nown + 1);
		vis[i]= 0;
	}
	return;
}
int main() {
	cin >> n;
	for(int i= 0; i < n; i++)
		for(int j= 0; j < n; j++) cin >> tmps[i][j];
	dfs(1);
	cout << "ERROR!" << endl;
	return 0;
}