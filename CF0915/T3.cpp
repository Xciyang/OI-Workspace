#include <iostream>
#include <stdio.h>
using namespace std;
int n;
char s[200005], t[200005], num[256];
int ab[200005], ba[200005], aptr;
struct ANS {
	int x, y;
} ans[200005];
int main() {
	cin >> n;
	cin >> (s + 1) >> (t + 1);
	for(int i= 1; i <= n; i++) {
		++num[s[i]], ++num[t[i]];
		if(s[i] == 'a' && t[i] == 'b') ab[++ab[0]]= i;
		if(s[i] == 'b' && t[i] == 'a') ba[++ba[0]]= i;
	}
	if(num['a'] % 2 || num['b'] % 2) {
		cout << -1 << endl;
        return 0;
	}
	for(int i= 2; i <= ab[0]; i+= 2) ans[++aptr].x= ab[i - 1], ans[aptr].y= ab[i];
	for(int i= 2; i <= ba[0]; i+= 2) ans[++aptr].x= ba[i - 1], ans[aptr].y= ba[i];
	if(ab[0] % 2) {
		ans[++aptr].x= ab[ab[0]], ans[aptr].y= ab[ab[0]];
		ans[++aptr].x= ab[ab[0]], ans[aptr].y= ba[ba[0]];
	}
	cout << aptr << endl;
	for(int i= 1; i <= aptr; i++) cout << ans[i].x << ' ' << ans[i].y << endl;
	return 0;
}