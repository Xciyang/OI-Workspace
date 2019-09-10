#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

#define maxn 400005
#define inf 0x3f3f3f3f
#define pn putchar('\n')
#define px(x) putchar(x)
#define ps putchar(' ')
#define pd puts("======================")
#define pj puts("++++++++++++++++++++++")

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
template<typename T>
inline T read(){
	T x=0;
	int y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
int f[maxn],ans[maxn],h[maxn],num,now,len;

struct edge{
	int pre,to,l;
}e[maxn<<1];
inline void add(int from,int to,int l){
	e[++num].pre=h[from],h[from]=num,e[num].to=to,e[num].l=l;
}
int gcd(int a,int b){
	if(!b)return a;
	return gcd(b,a%b);
}
void dfs(int node,int f,int len,int w){
	ans[len]=max(ans[len],w);
	int x;
	for(register int i=h[node];i;i=e[i].pre){
		x=e[i].to;
		if(x==f)continue;
		dfs(x,node,len+1,gcd(w,e[i].l));
	}
}
void dp(int node=1,int fa=0){
	f[node]=0;
	int x;
	for(register int i=h[node];i;i=e[i].pre){
		x=e[i].to;
		if(x==fa)continue;
		dp(x,node);
		if(e[i].l%now!=0)continue;
		len=max(len,f[node]+f[x]+1);
		f[node]=max(f[node],f[x]+1);
	}
}
int main(){
	int n=read(),x,y,z,tp=0;
	for(register int i=1;i<n;++i)x=read(),y=read(),tp=max(z=read(),tp),add(x,y,z),add(y,x,z);
	if(n<=3000){
		for(register int i=1;i<=n;++i)
			for(register int j=h[i];j;j=e[j].pre)
				dfs(e[j].to,i,1,e[j].l);
	}
	else {
		for(now=1;now<=tp;++now)len=0,dp(),ans[len]=now;
		for(register int i=n;i;--i)ans[i]=max(ans[i],ans[i+1]);
	}
	for(register int i=1;i<=n;++i)printf("%d\n",ans[i]);
}

