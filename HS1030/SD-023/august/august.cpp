#include<cstdio>
#include<iostream>
#define ll long long
using namespace std;
int cnt,n,k,t,a[20001];
ll o[20001];
int main(){
	freopen("august.in","r",stdin);
	freopen("august.out","w",stdout);
	int x,y;
	scanf("%d%d%d",&n,&k,&t);
	for (int i=1; i<=n; i++) scanf("%d",&a[i]);
	for (int i=n; i>=1; i--) a[i]-=a[i-1];
	int num=(n-k+1)%k;
	for (int i=1; i<=n; i++) o[i%k]+=a[i];
	for (int i=0; i<k; i++){
		if (i==num) continue;
		if (o[i]) cnt++;
	}
	if (!cnt) puts("Yes");
	else puts("No");
while (t--){
	scanf("%d%d",&x,&y);
	if (!y){
		if (!cnt) puts("Yes");
		else puts("No");
		continue;
	}
	a[x]+=y; a[x+1]-=y;
	int z=x%k;
	if (z!=num){
		o[z]+=y;
		if (o[z]==y) cnt++;
		else if (o[z]==0) cnt--;
	}
	z=(x+1)%k;
	if (z!=num){
		o[z]-=y;
		if (o[z]==-y) cnt++;
		else if (o[z]==0) cnt--;
	}
	if (!cnt) puts("Yes");
	else puts("No");
}
	return 0;
}
/*
5 2 5
1 1 1 2 1
3 -1
1 -1
3 1
3 1
1 -1
*/
