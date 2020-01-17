#include <iostream>
#include <stdio.h>
using namespace std;
#define MAX_N 100005
int N, sa[MAX_N], a[MAX_N];
#define cmp(i, j, k) (y[i] == y[j] && y[i + k] == y[j + k])
void Get_SA() {
	static int x[MAX_N], y[MAX_N], bln[MAX_N];
	int M = 122;
	for(int i = 1; i <= N; i++) bln[x[i] = a[i]]++;
	for(int i = 1; i <= M; i++) bln[i] += bln[i - 1];
	for(int i = N; i >= 1; i--) sa[bln[x[i]]--] = i;
	for(int k = 1; k <= N; k <<= 1) {
		int p = 0;
		for(int i = 0; i <= M; i++) y[i] = 0;
		for(int i = N - k + 1; i <= N; i++) y[++p] = i;
		for(int i = 1; i <= N; i++)
			if(sa[i] > k) y[++p] = sa[i] - k;
		for(int i = 0; i <= M; i++) bln[i] = 0;
		for(int i = 1; i <= N; i++) bln[x[y[i]]]++;
		for(int i = 1; i <= M; i++) bln[i] += bln[i - 1];
		for(int i = N; i >= 1; i--) sa[bln[x[y[i]]]--] = y[i];
		swap(x, y);
		x[sa[1]] = p = 1;
		for(int i = 2; i <= N; i++) x[sa[i]] = cmp(sa[i], sa[i - 1], k) ? p : ++p;
		if(p >= N) break;
		M = p;
	}
}
int main() {
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> a[i];
    Get_SA();
    return 0;
}