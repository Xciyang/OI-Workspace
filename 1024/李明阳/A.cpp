#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m, limitn, ans;
char tmps[4005], tmps2[4005];
char df[4005];
int check(int k) {
	int i, j;
	for(i= 1, j= 0; i <= n; i++) {
		if(tmps[i] == df[j]) ++j;
		if(j == k) return 0;
	}
	for(i= 1, j= 0; i <= m; i++) {
		if(tmps2[i] == df[j]) ++j;
		if(j == k) return 0;
	}
	return 1;
}
int Fn[4005][2], Fm[4005][2];
void init() {
	Fn[n + 1][0]= Fn[n + 1][1]= n + 1;
	Fm[m + 1][0]= Fm[m + 1][1]= m + 1;
	for(int i= n; i; i--) {
		if(tmps[i] == '0') Fn[i][0]= i, Fn[i][1]= Fn[i + 1][1];
		if(tmps[i] == '1') Fn[i][1]= i, Fn[i][0]= Fn[i + 1][0];
	}
	for(int i= m; i; i--) {
		if(tmps2[i] == '0') Fm[i][0]= i, Fm[i][1]= Fm[i + 1][1];
		if(tmps2[i] == '1') Fm[i][1]= i, Fm[i][0]= Fm[i + 1][0];
	}
	return;
}
int bdfs(int l, int r) {
	if(l > n && r > m) return 0;
	if(l > n) {
		if(Fm[r][0] >= Fm[r][1]) return bdfs(l, Fm[r][0] + 1) + 1;
		return bdfs(l, Fm[r][1] + 1) + 1;
	}
	else if(r > m) {
		if(Fn[l][0] >= Fn[l][1]) return bdfs(Fn[l][0] + 1, r) + 1;
		return bdfs(Fn[l][1] + 1, r) + 1;
	}
	else {
		int z1= Fn[l][0], o1= Fm[r][0];
		int z2= Fn[l][1], o2= Fm[r][1];
		if(z1 == z2) {
			if(o1 >= o2) return bdfs(z1, o1) + 1;
			return bdfs(z2, o2) + 1;
		}
		if(z1 > z2 && o1 >= o2)
			return bdfs(z1, o1) + 1;
		else if(z1 < z2 && o1 <= o2)
			return bdfs(z2, o2) + 1;
		else
			return min(bdfs(z1, o1), bdfs(z2, o2)) + 1;
	}
}
int trydfs(int nown) {
	if(nown > ans) return 0;
	df[nown]= '\0';
	if(nown && check(nown)) return 1;
	df[nown]= '0';
	if(trydfs(nown + 1)) return 1;
	df[nown]= '1';
	if(trydfs(nown + 1)) return 1;
	return 0;
}
int main() {
	cin >> n >> m;
	limitn= max(n, m);
	cin >> (tmps + 1) >> (tmps2 + 1);
    // init();
	// cout << bdfs(1, 1) << endl;
	for(ans= 1; ans <= limitn; ans++) 
		if(trydfs(0)) break;
	cout << df << endl;
	return 0;
}