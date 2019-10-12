#include <iostream>
#include <stdio.h>
using namespace std;
int n, pri[1005], flag[1005];
long long f[1005], ans;
void shai() {
	for(int i= 2; i <= n; i++) {
		if(!flag[i]) pri[++pri[0]]= i;
		for(int j= 1; j <= pri[0] && i * pri[j] <= n; j++) {
			flag[i * pri[j]]= 1;
			if(i % pri[j] == 0) break;
		}
	}
	return;
}
int main() {
	cin >> n;
	shai();
	f[0]= 1;
	for(int i= 1; i <= pri[0]; i++) {
		for(int j= n; j >= pri[i]; j--)
			for(int k= pri[i]; k <= j; k*= pri[i]) f[j]+= f[j - k];
	}
	for(int i= 0; i <= n; i++) ans+= f[i];
	cout << ans << endl;
	return 0;
}