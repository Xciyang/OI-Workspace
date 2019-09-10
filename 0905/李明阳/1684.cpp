#include <iostream>
#include <stdio.h>
#include <string.h>
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
int t, n, x[50], pos[50], nx[50];
int main() {
	t= read();
	while(t--) {
		n= read();
		for(int i= 1; i <= n; i++) nx[i]= x[i]= read(), pos[x[i]]= i;
		nx[n + 1]= x[n + 1]= n + 1;
		int r= n, ans= 0, tmpx;
		while(true) {
			for(; r; r--)
				if(x[r] != x[r + 1] - 1) break;
			if(r == 0) break;
			tmpx= pos[r];
			if(tmpx == 1) {
				for(int i= 1, j= r; i <= r; i++, j--) nx[j]= x[i], pos[nx[j]]= j;
				++ans, memcpy(x, nx, sizeof(nx));
			}
			else {
				for(int i= 1, j= tmpx; i <= tmpx; i++, j--) nx[j]= x[i], pos[nx[j]]= j;
				memcpy(x, nx, sizeof(nx));
				for(int i= 1, j= r; i <= r; i++, j--) nx[j]= x[i], pos[nx[j]]= j;
				ans+= 2, memcpy(x, nx, sizeof(nx));
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}