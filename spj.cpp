#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<fstream>
#define MAXN 300005
using namespace std;
void writ(const char s[],int point) {
	// fprintf(stderr, "%s\n", s);
	printf("%d\n",point);
	exit(0);
}
int a[MAXN],b[MAXN],c[MAXN], d[MAXN];
char st[10],tes[10];
int main(){
	freopen("input", "r", stdin);
	// ifstream file("input"),ans("user_out"),nul("answer");
	int n,m,k;
	// char s[10];
	// n=read_int("data1"),m=read_int("data1"),k=read_int("data1");
	cin>>n>>m>>k;
	// FILE *f = fopen("data1", "r");
	// for (int i=1; i<=k; i++) fscanf(f,"%d",&a[i]);
	// fclose(f);
	for(int i=1;i<=k;++i) {
		cin>>a[i];
	}
	freopen("answer", "r", stdin);
	scanf("%s", tes);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &d[i]);
	}
	freopen("user_out", "r", stdin);
	scanf("%s", st);
	if (tes[0]=='N'&&st[0]=='N') writ("hapi",100);
	if (tes[0]!=st[0]) writ("sb@xxx",0);
	for(int i=1;i<=n;++i)ans>>b[i];
	int len=0;
	for(int i=1;i<=n;++i){
		int pos=upper_bound(c+1,c+1+len,b[i])-c;
		len=max(len,pos);
		c[pos]=b[i];
	}
	if(len!=k) writ("sb@xxx",0);
	for(int i=1;i<=k;++i) {
		if(a[i]!=c[i]) {
			writ("sb@xxx",0);
		}
	}
	writ("hapi",100);
}