#include <iostream>
#include <thread>
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
using namespace std;
int n, m, a[200005], nowa[200005], tmpx, tmpy;
int qmin(int i) {
	return min(min(nowa[i % n + 1], nowa[(i + n - 2) % n + 1]), nowa[i]);
}
int qmax(int i) {
	return max(max(nowa[i % n + 1], nowa[(i + n - 2) % n + 1]), nowa[i]);
}
int ranse(int x, int &times) {
	int tot= 0;
	for(int i= 1; i <= n; i++)
		if(nowa[i] != x && (qmin(i) == x || qmax(i) == x)) ++times, nowa[i]= x;
	for(int i= n; i; i--)
		if(nowa[i] != x && (qmin(i) == x || qmax(i) == x)) ++times, nowa[i]= x;
	for(int i= 1; i <= n; i++) tot+= (nowa[i] == x);
	return tot;
}
int randomWork(int x) {
	for(int i= 1; i <= n; i++) nowa[i]= a[i];
	int tmpans= 0;
	int nowtot= ranse(x, tmpans);
	if(nowtot == 0) return -1;
	while(nowtot != n) {
		tmpx= rand() % n + 1, tmpy;
		while(nowa[tmpx] == x) tmpx= rand() % n + 1;
		tmpy= nowa[tmpx], nowa[tmpx]= qmin(tmpx);
		if(qmax(tmpx) == x) {
			tmpans+= 1 + (nowa[tmpx] != tmpy);
			nowa[tmpx]= x;
			nowtot= ranse(x, tmpans);
			continue;
		}
		nowa[tmpx]= tmpy, nowa[tmpx]= qmax(tmpx);
		if(qmin(tmpx) == x) {
			tmpans+= 1 + (nowa[tmpx] != tmpy);
			nowa[tmpx]= x;
			nowtot= ranse(x, tmpans);
			continue;
		}
		nowa[tmpx]= tmpy;
		if(qmin(tmpx) == tmpy && qmax(tmpx) == tmpy) continue;
		if(qmin(tmpx) == tmpy)
			nowa[tmpx]= qmax(tmpx), ++tmpans;
		else if(qmax(tmpx) == tmpy)
			nowa[tmpx]= qmin(tmpx), ++tmpans;
		else
			(nowa[tmpx]= rand() % 2 ? qmax(tmpx) : qmin(tmpx)), ++tmpans;
		nowtot= ranse(x, tmpans);
	}
	return tmpans;
}
int main() {
	srand(time(0));
	cin >> n >> m;
	for(int i= 1; i <= n; i++) cin >> a[i];
	for(int i= 1; i <= m; i++) {
		int ans= 0x3f3f3f3f;
		for(int j= 0; j < 1000; j++) ans= min(ans, randomWork(i));
		cout << ans << ' ';
	}
	return 0;
}