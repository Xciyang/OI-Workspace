#include <iostream>
#include <stdio.h>
using namespace std;
typedef long long ll;
ll n, m, mod;
ll exgcd(ll a, ll b, ll &x, ll &y) {
	if(!b) return x= 1, y= 0, a;
	ll res= exgcd(b, a % b, x, y), t;
	t= x, x= y, y= t - a / b * y;
	return res;
}

inline ll inv(ll a, ll p) {
	ll x, y;
	exgcd(a, p, x, y);
	return x > 0 ? x : x + p;
}

inline ll qpow(ll a, ll b, ll p) {
	ll ans= 1;
	while(b) {
		if(b & 1) ans= ans * a % p;
		a= a * a % p, b>>= 1;
	}
	return ans;
}
inline ll fac(ll a, ll p, ll pk) {
	if(!a) return 1;
	ll res= 1;
	for(register ll i= 2; i <= pk; i++)
		if(i % p) res= res * i % pk;
	res= qpow(res, a / pk, pk);
	for(register ll i= 2; i <= (a % pk); i++)
		if(i % p) res= res * i % pk;
	return res * fac(a / p, p, pk) % pk;
}
ll C(ll a, ll b, ll p, ll pk) {
	ll af= fac(a, p, pk), bf= fac(b, p, pk), abf= fac(a - b, p, pk), cnt= 0;
	for(register ll i= a; i; i/= p) cnt+= i / p;
	for(register ll i= b; i; i/= p) cnt-= i / p;
	for(register ll i= a - b; i; i/= p) cnt-= i / p;
	return af * inv(bf, pk) % pk * inv(abf, pk) % pk * qpow(p, cnt, pk) % pk;
}
inline ll CRT(ll a, ll p) {
	return a * inv(mod / p, p) % mod * (mod / p) % mod;
}
inline ll exlucas(ll a, ll b, ll p) {
	register ll res= 0, tmpp= p, pk;
	for(register int i= 2; i * i <= p; i++) {
		if(tmpp % i == 0) {
			pk= 1;
			while(tmpp % i == 0) pk*= i, tmpp/= i;
			res= (res + CRT(C(a, b, i, pk), pk)) % p;
		}
	}
	if(tmpp > 1) res= (res + CRT(C(a, b, tmpp, tmpp), tmpp)) % p;
	return res;
}
int main() {
	cin >> n >> m >> mod;
	cout << exlucas(n, m, mod) << endl;
	return 0;
}