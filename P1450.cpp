#include <iostream>
#include <stdio.h>
using namespace std;
int c[5], tot, d[5], sum;
long long f[100005], ans;
int main() {
	for(int i= 1; i <= 4; i++) cin >> c[i];
	cin >> tot;
	f[0]= 1;
	for(int i= 1; i <= 4; i++)
		for(int j= c[i]; j <= 100000; j++) f[j]+= f[j - c[i]];
	while(tot--) {
		for(int i= 1; i <= 4; i++) cin >> d[i];
		cin >> sum, ans= 0;
		for(int i= 0; i < (1 << 4); i++) {
			int addcut= 0, s= sum;
			for(int j= 1; j <= 4; j++)
				if(i >> (j - 1) & 1) s-= c[j] * (d[j] + 1), addcut^= 1;
			ans+= (addcut ? -1 : 1) * (s >= 0 ? f[s] : 0);
		}
		cout << ans << endl;
	}
	return 0;
}