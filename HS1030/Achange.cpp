#include <iostream>
#include <stdio.h>
using namespace std;
long long t, a, b;
unsigned long long ans1= 1, ans2= 1;
// 18446744073709551615ULL;
int main() {
	cin >> t;
	while(t--) {
		cin >> a >> b;
		ans1= ans2= 1;
		for(unsigned long long i= 1; i <= b; i++) ans1*= a, ans2*= i;
		if(ans1 <= ans2) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
	}
	return 0;
}