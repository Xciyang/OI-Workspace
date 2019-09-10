#include <iostream>
#include <stdio.h>
using namespace std;
int n, k, x[100], y[100], bans= 250000;
struct JZ {
	int x1, y1, x2, y2, flag;
} jz[10];
inline int judge(const JZ &jz1, const JZ &jz2) {
	return jz1.x2 >= jz2.x1 && jz1.x1 <= jz2.x2 && jz1.y2 >= jz2.y1 && jz1.y1 <= jz2.y2;
}
void dfs(int nown) {
	int nans= 0;
	for(int i= 1; i <= k; i++) {
		if(jz[i].flag) {
			for(int j= i + 1; j <= k; j++)
				if(jz[j].flag && judge(jz[i], jz[j])) return;
			nans+= (jz[i].x2 - jz[i].x1) * (jz[i].y2 - jz[i].y1);
		}
	}
	if(nans >= bans) return;
	if(nown == n + 1) {
		bans= nans;
		return;
	}
	for(int i= 1; i <= k; i++) {
		JZ ljz= jz[i];
		jz[i].flag= 1;
		jz[i].x1= min(jz[i].x1, x[nown]);
		jz[i].x2= max(jz[i].x2, x[nown]);
		jz[i].y1= min(jz[i].y1, y[nown]);
		jz[i].y2= max(jz[i].y2, y[nown]);
		dfs(nown + 1);
		jz[i]= ljz;
	}
	return;
}
int main() {
	cin >> n >> k;
	for(int i= 1; i <= n; i++) cin >> x[i] >> y[i];
	for(int i= 1; i <= k; i++) jz[i].x1= 505, jz[i].x2= 0, jz[i].y1= 505, jz[i].y2= 0;
	dfs(1);
	cout << bans << endl;
	return 0;
}