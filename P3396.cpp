#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
int n, m, nb, v[150001], sum[1500][1500], tmpx, tmpy;
char cmd;
int main() {
	cin >> n >> m, nb= sqrt(n);
	for(int i= 1; i <= n; i++) cin >> v[i];
	for(int i= 1; i <= nb; i++)
		for(int j= 1; j <= n; j++) sum[i][j % i]+= v[j];
	while(m--) {
		cin >> cmd >> tmpx >> tmpy;
		if(cmd == 'A') {
			if(tmpx <= nb)
				cout << sum[tmpx][tmpy] << endl;
			else {
				int ans= 0;
				for(int i= tmpy; i <= n; i+= tmpx) ans+= v[i];
				cout << ans << endl;
			}
		}
		else {
			for(int i= 1; i <= nb; i++) sum[i][tmpx % i]= sum[i][tmpx % i] - v[tmpx] + tmpy;
            v[tmpx]= tmpy;
		}
	}
	return 0;
}