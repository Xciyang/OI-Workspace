#include <iostream>
#include <stdio.h>
using namespace std;
int t, a, b, flag;
long double ans= 0;
int main() {
	freopen("yuuutsu.in", "r", stdin);
	freopen("yuuutsu.out", "w", stdout);
	cin >> t;
	while(t--) {
		cin >> a >> b;
		if(a == 1) {
			printf("Yes\n");
			continue;
		}
		if(a >= b) {
			printf("No\n");
			continue;
		}
		ans= 1, flag= 0;
		for(int i= 1, j= b; i <= j; i++, j--) {
			ans*= (long double)a * a / (i * j);
			if(i == j) ans*= (long double)j / a;
			if(ans < 1e-100) ans*= (long double)j / a, ++j;
			if(ans < 1e-300) {
				flag= 1;
				break;
			}
			if(ans > 1e100) ans*= (long double)i / a, --i;
			if(ans > 1e305) {
				flag= 2;
				break;
			}
		}
		if(flag) {
			if(flag == 1) {
				printf("Yes\n");
			}
			else {
				printf("No\n");
			}
		}
		else if(ans > 1) {
			printf("No\n");
		}
		else {
			printf("Yes\n");
		}
	}
	return 0;
}
/*
740 2000
No
735 2000
Yes
737 2000
Yes
738 2000
No
*/
// 50 200
// 50 6.2230152778611417071440640537801e+339
// 70 1.0461838291314357175018899611817e+369
// 75 1.028614585791589395686345235443e+375
// 100 1.e+400
// 200! = 7.8865786736479050355236321393219e+374
// 500 1000
// 367 4.6351548988157984065730574717422e+2564
// 500 9.3326361850321887899008954472382e+2698
// 369 1.0625910633348430481607229341123e+2567
// 1000! = 4.02387260077093773543702433923e+2567