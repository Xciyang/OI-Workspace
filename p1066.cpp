#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int k, w, ans[301], n, m, q, tmpa[301], tmpb[301], tmpx;
inline int gcd(int a, int b){
	return b ? gcd(b, a % b) : a;
}
inline int maxi(int a, int b){
	return a > b ? a : b;
}
void calcC(int a, int b){
	if(a < b) return;
	memset(tmpb, 0, sizeof(tmpb));
	memset(tmpa, 0, sizeof(tmpa));
	for(int i= 1; i <= b; i++) tmpa[i]= a + i - b, tmpb[i]= i;
	// Լ�� 
	for(int i= 1; i <= b; i++) {
		for(int j= b; j ; j--){
			if(tmpb[i] == 1) break;
			tmpx= gcd(tmpa[j], tmpb[i]);
			tmpa[j] /= tmpx, tmpb[i] /= tmpx;
		}
	}
	// ���
	memset(tmpb, 0, sizeof(tmpb));
	tmpb[0]= tmpb[1]= 1;
	for(int i= 1; i <= b; i++){
		if(tmpa[i] == 1) continue;
		tmpx= 0;
		for(int j= 1; j <= tmpb[0]; j++){
			tmpb[j] = tmpb[j] * tmpa[i] + tmpx;
			tmpx= tmpb[j] / 10;
			tmpb[j]%= 10;
			if(j == tmpb[0] && tmpx) ++tmpb[0];
		}
	}
	// ��� 
	ans[0]= maxi(ans[0], tmpb[0]);
	for(int i= 1; i <= ans[0]; i++){
		ans[i]+= tmpb[i];
		ans[i + 1] += ans[i] / 10;
		ans[i]%= 10;
	}
	if(ans[ans[0] + 1]) ++ans[0];
	return; 
}
int main(){
	cin >> k >> w;
	n= (1 << k) - 1, m= w / k, q= w % k;
	for(int i= m; i > 1; i--) calcC(n, i);
	q= (1 << q) - 1;
	if(q >= 1 && n > m){
		for(int i= 1; i <= q; i++) calcC(n - i, m);
	}
	for(int i= ans[0]; i; i--) cout << ans[i];
	cout << endl; 
	return 0;
}
