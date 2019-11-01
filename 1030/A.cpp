#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int t, n, m, fx[10], df[10];
char str[10][10];
int dfs(int nown) {
	if(nown == m + 1) {
		int dy= -1, dr= -1;
		df[1]= 0;
		for(int j= 1; j <= m; j++) df[1]+= ((str[1][j] == 'Y') << fx[j]);
		for(int i= 2; i <= n; i++) {
			df[i]= 0;
			for(int j= 1; j <= m; j++) df[i]+= ((str[i][j] == 'Y') << fx[j]);
			if(df[i] > dy)
				dr= dy, dy= df[i];
			else if(df[i] > dr)
				dr= df[i];
		}
		return dy > df[1] && df[1] > dr;
	}
	for(int i= 1; i <= m; i++) {
		if(fx[i]) continue;
		fx[i]= nown;
		if(dfs(nown + 1)) return 1;
		fx[i]= 0;
	}
	return 0;
}
int main() {
	cin >> t;
	while(t--) {
		cin >> n >> m;
		for(int i= 1; i <= n; i++) cin >> (str[i] + 1);
		for(int i= 1; i <= m; i++) fx[i]= 0;
		if(dfs(1)) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	return 0;
}