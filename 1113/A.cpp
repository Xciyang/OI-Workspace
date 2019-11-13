#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N= 100005;
int n;
double a[N], b[N];
double A, B, ans, c;
int main() {
	scanf("%d", &n);
	for(int i= 1; i <= n; i++) scanf("%lf", &a[i]);
	for(int i= 1; i <= n; i++) scanf("%lf", &b[i]);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	int t1= n, t2= n;
	A+= a[t1--];
	B+= b[t2--];
	c+= 2;
	for(int i= 3; i <= (n << 1); i++)
		if(i & 1) {
			double _A= A + a[t1], _c= c + 1;
			if(min(_A - _c, B - _c) >= ans) {
				ans= min(_A - _c, B - _c);
				A+= a[t1];
				c++;
			}
			t1--;
		}
		else {
			double _B= B + b[t2], _c= c + 1;
			if(min(A - _c, _B - _c) >= ans) {
				ans= min(A - _c, _B - _c);
				B+= a[t2];
				c++;
			}
			t2--;
		}
	printf("%.8lf\n", ans);
	return 0;
}
