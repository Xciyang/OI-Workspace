#include <iostream>
#include <stdio.h>
using namespace std;
int n;
int pr[10000007], phi[10000007], pcnt, inss[10000007];
long long ans, sum[10000007];
inline int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
void shai() {
	phi[1]= inss[1]= 1;
	for(int i= 2; i <= n; i++) {
		if(!inss[i]) phi[i]= i - 1, pr[++pcnt]= i;
		for(int j= 1; j <= pcnt && pr[j] * i <= n; j++) {
			inss[pr[j] * i]= 1;
			if(gcd(pr[j], i) == 1)
				phi[pr[j] * i]= phi[pr[j]] * phi[i];
			else
				phi[pr[j] * i]= pr[j] * phi[i];
			if(i % pr[j] == 0) break;
		}
	}
	return;
}
int main() {
	cin >> n;
	shai();
	for(int i= 1; i <= n; i++) sum[i]= sum[i - 1] + phi[i];
	for(int i= 1; i <= pcnt; i++) ans+= sum[n / pr[i]] * 2 - 1;
	cout << ans << endl;
	return 0;
}