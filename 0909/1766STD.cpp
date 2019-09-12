#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;

int n,m,k,f[55][55][55][55],pre[55],c[55],a,b,A[55],d[55][55];
int main()
{
	scanf("%d",&n);
	scanf("%d%d",&a,&b);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]), A[i]=c[i];
	sort(A+1,A+1+n);
	m=unique(A+1,A+1+n)-A-1;
	for(int i=1;i<=n;i++) k=lower_bound(A+1,A+1+m,c[i])-A, pre[k]=c[i], c[i]=k;
	memset(f,0x3f,sizeof(f)); memset(d,0x3f,sizeof(d));
	for(int i=1;i<=n;i++) 
		for(int l=1;l<=c[i];l++)
		for(int r=c[i];r<=m;r++) f[i][i][l][r]=0;
		
	for(int len=0;len<n;len++)
	{
		for(int l=1;l+len<=n;l++)
		{
			int r=l+len;
			for(int i=1;i<=m;i++)
				for(int j=i;j<=m;j++) if(f[l][r][i][j]!=0x3f3f3f3f)
					d[l][r]=min(d[l][r],f[l][r][i][j]+a+b*(pre[j]-pre[i])*(pre[j]-pre[i]));
			for(int i=l+1;i<=r;i++) d[l][r]=min(d[l][r],d[l][i-1]+d[i][r]);
		}
		for(int l=1;l+len+1<=n;l++)
		{
			int r=l+len+1;
			f[l][r][c[r]][c[r]]=min(f[l][r][c[r]][c[r]],d[l][r-1]);
			f[l][r][c[l]][c[l]]=min(f[l][r][c[l]][c[l]],d[l+1][r]);

			for(int i=1;i<=m;i++)
				for(int j=i;j<=m;j++) 
					for(int k=l+1;k<=r;k++) 
						f[l][r][i][j]=min(f[l][r][i][j],f[l][k-1][i][j]+f[k][r][i][j]);
			for(int i=m;i>=1;i--)	
				for(int j=1;j<=m;j++) f[l][r][i][j]=min(f[l][r][i][j],min(f[l][r][i+1][j],f[l][r][i][j-1]));
		}
	}
	printf("%d",d[1][n]);
}
