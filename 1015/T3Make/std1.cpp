#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;
#define lll __int128

ll max_factor;

inline ll gcd(ll a,ll b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}

inline ll qp(ll x,ll p,ll mod)
{
	ll ans=1;
	while(p)
	{
		if(p&1)
			ans=(lll)ans*x%mod;
		x=(lll)x*x%mod;
		p>>=1;
	}
	return ans;
}

inline bool mr(ll x,ll b)
{
	ll k=x-1;
	while(k)
	{
		ll cur=qp(b,k,x);
		if(cur!=1 && cur!=x-1)
			return false;
		if((k&1)==1 || cur==x-1)
			return true;
		k>>=1;
	}
	return true;
}

inline bool prime(ll x)
{
	if(x==46856248255981ll || x<2)
		return false;
	if(x==2 || x==3 || x==7 || x==61 || x==24251)
		return true;
	return mr(x,2)&&mr(x,61);
}

inline ll f(ll x,ll c,ll n)
{
	return ((lll)x*x+c)%n;
}

inline ll PR(ll x)
{
	ll s=0,t=0,c=1ll*rand()%(x-1)+1;
	int stp=0,goal=1;
	ll val=1;
	for(goal=1;;goal<<=1,s=t,val=1)
	{
		for(stp=1;stp<=goal;++stp)
		{
			t=f(t,c,x);
			val=(lll)val*abs(t-s)%x;
			if((stp%127)==0)
			{
				ll d=gcd(val,x);
				if(d>1)
					return d;
			}
		}
		ll d=gcd(val,x);
		if(d>1)
			return d;
	}
}

inline void fac(ll x)
{
	if(x<=max_factor || x<2)
		return;
	if(prime(x))
	{
		max_factor=max_factor>x?max_factor:x;
		return;	 
	}
	ll p=x;
	while(p>=x)
		p=PR(x);
	while((x%p)==0)
		x/=p;
	fac(x),fac(p);
}

//^Template^

int tot;
int cnt[25];
const int mod = 998244353;
map<unsigned long long,int> ans;
unsigned long long bas = 131;

long long qpow(long long base,int tms)
{
	long long tmp = 1;
	while(tms)
	{
		if(tms & 1) tmp = tmp * base % mod;
		base = base * base % mod;
		tms >>= 1;
	}
	return tmp;
}

int f(int a)
{
	return __builtin_popcount(a) & 1 ? -1 : 1;
}

long long doit(int S)
{
	int C[25] = {0};
	for(int i = 1;i <= tot; ++ i)
		C[i] = cnt[i] - ((S & 1 << i - 1) ? 1 : 0);
	sort(C + 1,C + 1 + tot);
	unsigned long long ha = 0;
	for(int i = 1;i <= tot; ++ i)
		ha = ha * bas + C[i] + 1;
	if(ans.count(ha)) return ans[ha];
	int fuc = 0;
	for(int i = 1;i <= tot; ++ i) if(C[i]) fuc |= 1 << i - 1;
	long long res = 0;
	for(int j = fuc;;j = (j - 1) & fuc)
	{
		long long typ = 1;
		for(int i = 1;i <= tot; ++ i)
			typ *= C[i] - ((j & 1 << i - 1) ? 1 : 0) + 1;
		res += f(j) * (qpow(2,typ) - 1) % mod;
		res = (res % mod + mod) % mod;
		if(j == 0) break;
	}
	return ans[ha] = res;
}

int main()
{
	srand((unsigned long long)(new char));
	long long n; scanf("%lld",&n);
	if(n == 1)
	{
		printf("1\n");
		return 0;
	}
	fac(n);
	tot ++;
	while(n % max_factor == 0) n /= max_factor,cnt[tot] ++;
	for(int i = 2;i * 1ll * i <= n; ++ i)
		if(n % i == 0)
		{
			tot ++;
			while(n % i == 0) n /= i,cnt[tot] ++;
		}
	if(n > 1) cnt[++ tot] = 1;
	sort(cnt + 1,cnt + 1 + tot);
	long long ans = 0;
	int all = (1 << tot) - 1;
	for(int i = 0;i <= all; ++ i)
	{
		ans += f(i) * doit(i);
		ans = (ans % mod + mod) % mod;
	}
	printf("%lld\n",ans);
	
	return 0;
}
