#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
int a, b, ans;
queue< int > qu;
void dfs(int num, long long nownum, int nowbase) {
	if(nownum > b) return;
	if(!num) {
		int last= nownum / (nowbase / 10);
		if(!last) return;
		dfs(num, nownum + (long long)last * nowbase, nowbase * 10);
		if(nownum >= a && nownum <= b) ++ans;
		if(nowbase < b) qu.push(nownum);
		return;
	}
	int last= nownum / (nowbase / 10), endw= num % 10;
	num/= 10;
	if(last >= endw) dfs(num, nownum + (long long)(last - endw) * nowbase, nowbase * 10);
	if(endw && last + endw < 10) dfs(num, nownum + (long long)(last + endw) * nowbase, nowbase * 10);
	return;
}
// last : the highest bit
int main() {
	cin >> a >> b;
	qu.push(7);
	if(a <= 7 && 7 <= b) ++ans;
	while(!qu.empty()) {
		for(int i= 0; i < 10; i++) dfs(qu.front(), i, 10);
		qu.pop();
	}
	cout << ans << endl;
	return 0;
}