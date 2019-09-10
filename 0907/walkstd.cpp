#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define N 800003
#define M 1000006
using namespace std;
int head[M],nxt1[N],x1[N],y2[N],cnt,sz,ans[N];
int point[M],nxt[N],v[N],tot,st[N],top,vis[N],len;
int n,m,mark;
void add(int k,int x,int y)
{
    cnt++; nxt1[cnt]=head[k]; head[k]=cnt; x1[cnt]=x; y2[cnt]=y;
}
void add1(int x,int y)
{
    tot++; nxt[tot]=point[x]; point[x]=tot; v[tot]=y;
    tot++; nxt[tot]=point[y]; point[y]=tot; v[tot]=x;
    st[++top]=x; st[++top]=y;
}
int dfs(int x,int fa)
{
    vis[x]=sz;
    int l=0,r=0;
    for (int i=point[x];i;i=nxt[i])
     if (vis[v[i]]!=sz&&v[i]!=fa){
        int t=dfs(v[i],x);
        if (t+1>l) r=l,l=max(l,t+1);
        else if (t+1>r) r=max(r,t+1);
     }
    len=max(len,l+r);
    return l;
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<n;i++)
     {
        int a,b,c; scanf("%d%d%d",&a,&b,&c);
        add(c,a,b);
     }
    for (int i=1;i<=1000000;i++){
        for (int j=i;j<=1000000;j+=i)
         for (int k=head[j];k;k=nxt1[k])
          add1(x1[k],y2[k]);
        mark=i; ++sz; len=0;
        for (int j=1;j<=top;j++)
         if (vis[st[j]]!=sz) dfs(st[j],0);
        ans[len]=max(ans[len],i);
        for (int j=1;j<=top;j++)
         point[st[j]]=0;
        tot=0; top=0;
    }
    for (int i=n;i>=1;i--)  ans[i]=max(ans[i],ans[i+1]);
    for (int i=1;i<=n;i++) printf("%d\n",ans[i]);
}