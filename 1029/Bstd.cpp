#include <cstdio>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;
struct Point {
	int x, y;
	int id;
} a[300005];
int n, ans[300005], top;
bool flag[300005];
bool check(ll v) {
	top= 0;
	int nowx= 1, nowy= 1;
	for(int i= 1; i <= n; i++) flag[i]= 0;
	bool f= 1;
	while(f) {
		f= 0;
		for(int i= 1; i <= n; i++) {
			if(flag[i] == 1) continue;
			if(flag[i] == 0 && max(0, a[i].x - nowx) + max(0, a[i].y - nowy) <= v) {
				ans[++top]= a[i].id;
				nowx= max(nowx, a[i].x);
				nowy= max(nowy, a[i].y);
				flag[i]= 1;
				f= 1;
			}
		}
	}
	for(int i= 1; i <= n; i++)
		if(flag[i] == 0) return 0;
	return 1;
}
int main() {
	scanf("%d", &n);
	for(int i= 1; i <= n; i++) {
		scanf("%d%d", &a[i].x, &a[i].y);
		a[i].id= i;
	}
	random_shuffle(a + 1, a + n + 1);
	int l= 0, r= 2147483647;
	while(l <= r) {
		int mid= (l + r) / 2;
		if(check(mid))
			r= mid - 1;
		else
			l= mid + 1;
	}
	top= 0;
	int nowx= 1, nowy= 1;
	for(int i= 1; i <= n; i++) flag[i]= 0;
	bool f= 1;
	while(f) {
		f= 0;
		for(int i= 1; i <= n; i++) {
			if(flag[i] == 1) continue;
			if(flag[i] == 0 && max(0, a[i].x - nowx) + max(0, a[i].y - nowy) <= l) {
				ans[++top]= a[i].id;
				nowx= max(nowx, a[i].x);
				nowy= max(nowy, a[i].y);
				flag[i]= 1;
				f= 1;
			}
		}
	}
	for(int i= 1; i <= n; i++) printf("%d ", ans[i]);
	printf("\n");
	return 0;
}
