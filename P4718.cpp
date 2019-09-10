#include <iostream>
#include <stdio.h>
using namespace std;
typedef long long ll;
__int128_t quickmul(ll a, ll b) {
	return (__int128_t)a * b;
}
ll quickpow(ll a, ll b, ll p) {
	ll ans= 1;
	while(b) {
		if(b & 1) ans= quickmul(ans, a) % p;
		b>>= 1, a= quickmul(a, a) % p;
	}
	return ans % p;
}
ll gcd(ll a, ll b) {
	if(!b) return a;
	return gcd(b, a % b);
}
ll absmns(ll a, ll b) {
	return a > b ? a - b : b - a;
}
template < typename T >
void read(T &res) {
	char ch= getchar();
	T f= 1, e= 0;
	while(ch < '0' || ch > '9') {
		if(ch == '-') f= -1;
		ch= getchar();
	}
	while(ch >= '0' && ch <= '9') e= e * 10 + ch - '0', ch= getchar();
	res= f * e;
	return;
}
template < typename T >
int put(const T &ins) {
	if(ins < 0) return putchar('-'), put(-ins);
	if(ins > 9) put(ins / 10);
	return putchar('0' + ins % 10);
}
int n;
int main() {
	cin >> n;
	while(n--) {
        
	}
	return 0;
}