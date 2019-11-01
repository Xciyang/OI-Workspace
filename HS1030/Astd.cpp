#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
double a, b, x, y;
int t;
int main() {
	// freopen("yuuutsu.in", "r", stdin);
	// freopen("yuuutsu.out", "w", stdout);
	scanf("%d", &t);
	while(t--) {
		scanf("%lf%lf", &x, &y);
		a= 1.0 * log2(x) * y;
		b= 0;
		for(int i= 1; i <= y; i++) b+= log2(i);
		if(a <= b)
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}