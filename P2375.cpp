#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, t, nxt[1000001], num[1000001];
long long ans;
char str[1000001];
void kmp() {
	nxt[0]= -1, num[0]= 1;
	for(int i= 0, j; i < n; i++) {
		j= nxt[i];
		while(j != -1 && str[i] != str[j]) j= nxt[j];
		nxt[i + 1]= j + 1, num[i + 1]= num[j + 1] + 1;
	}
    for(int i= 1, j= 0; i < n; i++) {
        while(j != -1 && str[i] != str[j]) j= nxt[j];
        ++j;
        while((j << 1) > i + 1) j= nxt[j];
        ans= ans * num[j] % 1000000007;
    }
	return;
}
int main() {
	cin >> t;
	while(t--) {
		cin >> str, n= strlen(str), ans=1;
        kmp();
        cout << ans << endl;
	}
	return 0;
}