#include <iostream>
#include <stdio.h>
using namespace std;
int n, w, tmpx, tmpy, tmpz, v[5005], m[5005], cnt, f[1000006];
int main() {
	cin >> n >> w;
	for(int i= 1; i <= n; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		for(int j= 1; tmpz >= j; j<<= 1) v[++cnt]= tmpx * j, m[cnt]= tmpy * j, tmpz-= j;
		if(tmpz) v[++cnt]= tmpx * tmpz, m[cnt]= tmpy * tmpz;
	}
	for(int i= 1; i <= cnt; i++)
		for(int j= w; j >= m[i]; j--) f[j]= max(f[j], f[j - m[i]] + v[i]);
	cout << f[w] << endl;
	return 0;
}