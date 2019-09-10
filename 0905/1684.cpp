#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
inline int read() {
	int e= 0, f= 1;
	char ch= getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') e= e * 10 + ch - '0', ch= getchar();
	return e * f;
}
inline int abs(int x) {
	return x < 0 ? -x : x;
}
int t, n, x[50], ans, flag;
void IDA(int step, int lastl) {
	int f= 1, cnt= 0;
	for(int i= 1; i < n; i++) {
		cnt+= (abs(x[i + 1] - x[i]) > 1);
		if(x[i] != i) f= 0;
	}
	if(f) {
		flag= 1, ans= step;
		return;
	}
	if(step + cnt > ans || step == ans) return;
	for(int i= 1; i <= n; i++) {
		if(i == lastl) continue;
		reverse(x + 1, x + i + 1);
		IDA(step + 1, i);
		if(flag) return;
		reverse(x + 1, x + i + 1);
	}
	return;
}
int main() {
	t= read();
	while(t--) {
		n= read(), flag= 0;
		for(int i= 1; i <= n; i++) x[i]= read();
		for(ans= 0;; ans++) {
			IDA(0, 0);
			if(flag) break;
		}
		printf("%d\n", ans);
	}
	return 0;
}