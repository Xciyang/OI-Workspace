#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <map>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
using namespace std;
typedef long long ll;
const int mod=998244353;
const int inf = 1 << 30;
map<ll, int>mp;
namespace rho{
    inline ll mul(ll a,ll b,ll p){
        a %= p; b %= p;
        if(p<=1e9)return 1ll*a*b%p;
        if(p<=1e12)return (((a*(b>>20)%p)<<20)%p+a*(b&(1<<20)-1))%p;
        ll d=1ll*floor(a*(long double)b/p);
        ll res=(a*b-d*p)%p;if(res<0)res += p;
        return res;
    }

    inline ll pw(ll a,ll b,ll mod){
        ll res=1;
        for(;b;b>>=1){
            if(b&1)res=mul(res,a,mod);
            a=mul(a,a,mod);
        }
        return res;
    }

    inline int check(ll a,ll x,ll times,ll n){
        ll tmp=pw(a,x,n);
        while(times --> 0){
            ll lst=mul(tmp,tmp,n);
            if(lst==1&&tmp!=1&&tmp!=n-1)return 1;
            tmp=lst;
        }
        return tmp!=1;
    }
    int base[]={2,3,5,7,11,13,17,19,23};
    const int S=8;
    int miller(ll n){
        for(int i=0;i<=S;i++){
            if(n==base[i])return 1;
            if(n%base[i]==0)return 0;
        }
        ll x=n-1,times=0;
        while(x%2==0)x/=2,++times;
        for(int i=0;i<=S;i++){
            if(check(base[i],x,times,n))return 0;
        }
        return 1;
    }

#define F(x) ((mul(x,x,n)+c)%n)
    inline ll rho(ll n,ll c){
        ll x=rand()%n,y=F(x);
        while(x^y){
            ll w=__gcd(abs(x-y),n);
            if(w>1&&w<n)return w;
            x=F(x);y=F(y);y=F(y);
        }
        return 0;
    }

    void calc(ll x){
        if(miller(x)){
            ++ mp[x];
            return ;
        }
        ll res=0;
        while((res=rho(x,rand()%x))==0);
        calc(res);calc(x/res);
    }
}
using namespace rho;

const int maxn=23;
ll p[maxn],c[maxn],tot=0;
int ans=0;

void dfs(int cur,int k,int d){
    if(cur > tot){(ans += 1ll*(pw(2,d,mod)+mod-1)%mod*k%mod) %= mod;return;}
    dfs(cur+1,k,1ll*d*(c[cur]+1)%(mod-1));dfs(cur+1,2ll*(mod-k)%mod,1ll*d*c[cur]%(mod-1));if(c[cur]>1)dfs(cur+1,k,1ll*d*(c[cur]-1)%(mod-1));
}

int main(){
    srand(time(0));
    ll n;scanf("%lld",&n);
    if(n==1){puts("1");return 0;}
    calc(n);
    for(map<ll,int>::iterator it=mp.begin();it!=mp.end();it++){
        p[++tot]=it->first;c[tot]=it->second;
    }
    dfs(1,1,1);
    printf("%d\n",ans);
    return 0;
}
