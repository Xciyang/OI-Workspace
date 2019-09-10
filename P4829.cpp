#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
int n, m, seed, b[10000007];
long long tmpx, tmpy, tmpz, a[10000007];
void generate_array() {
	unsigned x= seed;
	for(int i= 0; i < n; ++i) {
		x^= x << 13;
		x^= x >> 17;
		x^= x << 5;
		a[i]= x % m + 1;
	}
	return;
}
void msort() {
	for(int i= 0; i < n; i++) ++b[a[i]];
	for(int i= 1, cptr= 0; i <= m; i++)
		while(b[i]) a[cptr++]= i, --b[i];
	return;
}
queue< long long > qu;
int nptr;
long long getnext() {
	if(qu.empty()) return a[nptr++];
	tmpx= qu.front();
	if(nptr == n || a[nptr] > tmpx) {
		qu.pop();
		return tmpx;
	}
	return a[nptr++];
}
int main() {
	cin >> n >> m >> seed;
	generate_array(), msort();
	for(int i= 1; i < n; i++) {
		tmpy= getnext(), tmpz= getnext();
		qu.push(max(tmpy << 1, tmpz));
	}
	cout << qu.front() << endl;
	return 0;
}