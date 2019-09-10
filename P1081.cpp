#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, x0, q, pre[100005], nxt[100005], idd[100005], xa[100005], xb[100005], fxa[100005][18], fxb[100005][18], f[100005][18], ans, tmpx, tmpy;
struct CITY {
	int h, id;
	bool operator<(const CITY &c2) const {
		return h < c2.h;
	}
} cs[100005];
inline int judgelr(int l, int r, int nh) {
	if(!l) return 0;
	if(!r) return 1;
	return nh - cs[l].h <= cs[r].h - nh;
}
inline int abs(int x) {
	return x < 0 ? -x : x;
}
inline double query(int be, int x) {
	int cnt1= 0, cnt2= 0;
	for(int i= 17; i >= 0; i--)
		if(f[be][i] && cnt1 + cnt2 + fxa[be][i] + fxb[be][i] <= x) cnt1+= fxa[be][i], cnt2+= fxb[be][i], be= f[be][i];
	if(xa[be] && cnt1 + cnt2 + fxa[be][0] <= x) cnt1+= fxa[be][0], be= xa[be];
	return cnt2 ? (double)cnt1 / cnt2 : 0x7f7f7f7f;
}
int cnta, cntb;
inline void query2(int be, int x) {
	cnta= cntb= 0;
	for(int i= 17; i >= 0; i--)
		if(f[be][i] && cnta + cntb + fxa[be][i] + fxb[be][i] <= x) cnta+= fxa[be][i], cntb+= fxb[be][i], be= f[be][i];
	if(xa[be] && cnta + cntb + fxa[be][0] <= x) cnta+= fxa[be][0], be= xa[be];
	return;
}
inline double absl(double x) {
	return x < 0 ? -x : x;
}
int main() {
	scanf("%d", &n);
	for(int i= 1; i <= n; i++) scanf("%d", &cs[i].h), cs[i].id= i;
	sort(cs + 1, cs + n + 1);
	for(int i= 1; i <= n; i++) idd[cs[i].id]= i, nxt[i]= i + 1, pre[i]= i - 1;
	nxt[n]= 0;
	for(int i= 1; i <= n; i++) {
		tmpx= idd[i];
		if(judgelr(pre[tmpx], nxt[tmpx], cs[tmpx].h)) {
			xb[i]= cs[pre[tmpx]].id;
			xa[i]= cs[((!nxt[tmpx] || (pre[pre[tmpx]] && cs[tmpx].h - cs[pre[pre[tmpx]]].h <= cs[nxt[tmpx]].h - cs[tmpx].h)) ? pre[pre[tmpx]] : nxt[tmpx])].id;
		}
		else {
			xb[i]= cs[nxt[tmpx]].id;
			xa[i]= cs[((!pre[tmpx] || (nxt[nxt[tmpx]] && cs[tmpx].h - cs[pre[tmpx]].h > cs[nxt[nxt[tmpx]]].h - cs[tmpx].h)) ? nxt[nxt[tmpx]] : pre[tmpx])].id;
		}
		if(pre[tmpx]) nxt[pre[tmpx]]= nxt[tmpx];
		if(nxt[tmpx]) pre[nxt[tmpx]]= pre[tmpx];
	}
	for(int i= 1; i <= n; i++) {
		f[i][0]= xb[xa[i]];
		fxa[i][0]= xa[i] > 0 ? abs(cs[idd[xa[i]]].h - cs[idd[i]].h) : 0;
		fxb[i][0]= f[i][0] && xa[i] ? abs(cs[idd[f[i][0]]].h - cs[idd[xa[i]]].h) : 0;
	}
	for(int j= 1; j < 18; j++) {
		for(int i= 1; i <= n; i++) {
			f[i][j]= f[f[i][j - 1]][j - 1];
			fxa[i][j]= fxa[i][j - 1] + fxa[f[i][j - 1]][j - 1];
			fxb[i][j]= fxb[i][j - 1] + fxb[f[i][j - 1]][j - 1];
		}
	}
	double tmpd= 0x7f7f7f7f, tmpdd;
	scanf("%d", &x0);
	for(int i= 1; i <= n; i++) {
		tmpdd= query(i, x0);
		if(absl(tmpdd - tmpd) < 1e-6) {
			if(cs[idd[i]].h > cs[idd[ans]].h) ans= i;
		}
		else if(tmpdd < tmpd)
			ans= i, tmpd= tmpdd;
	}
	printf("%d\n", ans);
	scanf("%d", &q);
	while(q--) {
		scanf("%d%d", &tmpx, &tmpy);
		query2(tmpx, tmpy);
		printf("%d %d\n", cnta, cntb);
	}
	return 0;
}