#include<cstdio>
#include<vector>
#include<iostream>
#define ll long long
using namespace std;
struct node{
	int next,to;
}w[200001];
vector<int> v[200001];
ll ans;
int cnt,head[200001],flu[200001],tot,dfn[200001];
int dp[2][200001][19],logg[400001],ed[200001],n,num;
int a[200001],deep[200001],d[200001],st[400001][20];
inline void add(int x,int y){
	w[++cnt].next=head[x];
	w[cnt].to=y; head[x]=cnt;
}
inline int cmp1(int x,int y){if (deep[x]<deep[y]) return x; return y;}
inline int cmp2(int x,int y){if (dfn[x]<dfn[y]) return x; return y;}
inline int cmp3(int x,int y){if (dfn[x]>dfn[y]) return x; return y;}
void dfs(int x){
	dfn[x]=++tot;
	flu[x]=++num; st[num][0]=x;
	for (int i=head[x]; i; i=w[i].next){
		deep[w[i].to]=deep[x]+1;
		dfs(w[i].to);
		st[++num][0]=x;
	}
	ed[x]=tot;
}
inline int lca(int x,int y){
	x=flu[x],y=flu[y];
	if (x>y) swap(x,y);
	int k=logg[y-x+1];
	return cmp1(st[x][k],st[y-(1<<k)+1][k]);
}
inline int query(int x,int y,int z){
	int k=logg[y-x+1];
	if (!z) return cmp2(dp[z][x][k],dp[z][y-(1<<k)+1][k]);
	return cmp3(dp[z][x][k],dp[z][y-(1<<k)+1][k]);
}
int main(){
	freopen("sagittarius.in","r",stdin);
	freopen("sagittarius.out","w",stdout);
	scanf("%d",&n); logg[0]=-1;
	for (int i=2,x; i<=n; i++)
		scanf("%d",&x),add(x,i);
	for (int i=1; i<=n; i++) scanf("%d",&a[i]);
	for (int i=1; i<=n; i++) scanf("%d",&d[i]);
	dfs(1);
	for (int i=2; i<=num; i++) logg[i]=logg[i>>1]+1;
	for (int i=1; i<=n; i++) dp[0][i][0]=dp[1][i][0]=a[i];
	for (int j=1; j<=logg[n]; j++)
		for (int i=1; i+(1<<j)-1<=n; i++){
			dp[0][i][j]=cmp2(dp[0][i][j-1],dp[0][i+(1<<(j-1))][j-1]);
			dp[1][i][j]=cmp3(dp[1][i][j-1],dp[1][i+(1<<(j-1))][j-1]);
		}
	for (int j=1; j<=logg[num]; j++)
		for (int i=1; i+(1<<j)-1<=num; i++)
			st[i][j]=cmp1(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	for (int i=1; i<n; i++){
		v[lca(a[i],a[i+1])].push_back(i);
//		printf("%d\n",lca(a[i],a[i+1]));
	}
for (int x=1; x<=n; x++){
	ll res=1; int las=0;
	for (int i=0; i<v[x].size(); i++){
		int z=v[x][i],l,mid,r,nl=0,nr=0;
		l=0,r=z-las-1;
		while (l<=r){
			mid=(l+r)>>1;
			if (dfn[x]<=dfn[query(z-mid,z,0)]
			  &&ed[x]>=dfn[query(z-mid,z,1)]) l=mid+1,nl=mid;
			
			else r=mid-1;
		}
		z++,l=0,r=n-z;
		while (l<=r){
			mid=(l+r)>>1;
			if (dfn[x]<=dfn[query(z,z+mid,0)]
			  &&ed[x]>=dfn[query(z,z+mid,1)]) l=mid+1,nr=mid;
			else r=mid-1;
		}
		res+=1ll*(nl+1)*(nr+1); las=z-1;
	}
	ans+=1ll*res*d[x];
//	printf("%lld ",res);
}
//	puts("");
	printf("%lld\n",ans);
	return 0;
}
/*
7
1 1 3 3 5 5
7 2 3 1 4 5 6
1 1 1 1 1 1 1
*/
