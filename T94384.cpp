#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
char ZFC[2003], changeto, cnt[26], len;
long double ans;
long double dfs(int nown) {
	if(nown == len + 1) return 1;
	if(ZFC[nown] == changeto) return dfs(nown + 1);
	++cnt[changeto];
	int res= (double)(cnt[changeto] - 1) / len / len * dfs(nown + 1);
	--cnt[changeto];
	return res;
}
int main() {
	scanf("%s", ZFC + 1), len= strlen(ZFC + 1);
	for(int i= 1; i <= len; i++) ++cnt[ZFC[i]-= 'A'];
	for(int i= 0; i < 26; i++) {	
		if(!cnt[changeto]) continue;
		changeto= i;
		ans+= dfs(1);
	}
	printf("%.1lf\n", ans);
	return 0;
}