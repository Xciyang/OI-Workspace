#include <iostream>
#include <stdio.h>
using namespace std;
int s, b, mmp[100], mpp, nb[10], pp[6][6][6][6][6], tmpx;
struct PY {
	int n, k[10], p;
} ps[100];
struct WP {
	int k, p;
} wss[6];
void dfs(int nown) {
	if(!nown) {
		int &res= pp[nb[1]][nb[2]][nb[3]][nb[4]][nb[5]]= 0;
		for(int i= 1; i <= b; i++) res+= nb[i] * wss[i].p;
		for(int i= 1; i <= s; i++) {
			tmpx= 0;
			for(int j= 1; j <= b; j++)
				if(nb[j] < ps[i].k[j]) goto failed;
			res= min(res, pp[nb[1] - ps[i].k[1]][nb[2] - ps[i].k[2]][nb[3] - ps[i].k[3]][nb[4] - ps[i].k[4]][nb[5] - ps[i].k[5]] + ps[i].p);
		failed:;
		}
		return;
	}
	for(nb[nown]= 0; nb[nown] <= wss[nown].k; nb[nown]++) dfs(nown - 1);
	return;
}
int main() {
	cin >> s;
	for(int i= 1; i <= s; i++) {
		cin >> ps[i].n;
		for(int j= 1; j <= ps[i].n; j++) {
			cin >> tmpx;
			if(!mmp[tmpx]) mmp[tmpx]= ++mpp;
			cin >> ps[i].k[mmp[tmpx]];
		}
		cin >> ps[i].p;
	}
	cin >> b;
	for(int i= 1; i <= b; i++) {
		cin >> tmpx;
		if(!mmp[tmpx]) mmp[tmpx]= ++mpp;
		cin >> wss[mmp[tmpx]].k >> wss[mmp[tmpx]].p;
	}
	dfs(b);
	cout << pp[wss[1].k][wss[2].k][wss[3].k][wss[4].k][wss[5].k] << endl;
	return 0;
}